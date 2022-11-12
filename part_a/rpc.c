#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

//for open
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_APPEND)
#define CREATE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


int main(int argc, char *argv[]){
    int     p2c[2], c2p[2]; // for pipes
    int     xx[2];
    pid_t   pid;
    char    w_buf[1000], r_buf[10000], r_buf2[10000];

    char input1[1000], input2[1000];  // for use these to take char input with scanf

    pipe(p2c);
    pipe(c2p);
    pipe(xx);

    if((pid=fork()) == -1) {     // if fork fail
        fprintf(stderr, "fork() failed.\n");
        exit(-1);
    }

    if(pid > 0) {
        /**
         * This is the code for the parent process.
         */
        char line[1000];
        int nbytes, nbytes2;

        /**
         * The parent should close the ends of the pipes that it will not use.
         */
        close(p2c[0]);
        close(c2p[1]);
        close(xx[1]);  //pipe for STDERR_FILENO, we need different pipe for detect to print FAIL OR SUCCESS

        // taking two input fromm console
        scanf("%s",input1);
        scanf("%s",input2);


        //concentrate the strings,result like "10 20\n"
        strcat(input1," ");
        strcat(input1,input2);
        strcat(input1,"\n");


        /**
         * Send a message to the child process through the forward pipe (p2c).
         * Don't forget to add "1" to the length of the string for the NULL character.
         */

        write(p2c[1], input1, strlen(input1));


        /**
         * Read the child's output through the reverse pipe (c2p) and (xx).
         */

        nbytes = read(c2p[0], r_buf, sizeof(r_buf));
        nbytes2= read(xx[0], r_buf2, sizeof(r_buf2));


       int fd;

       char *source2;
       source2=argv[2];  // set the second argv to souurce2 char. it is the pat of output txt
       fd=open(source2, CREATE_FLAGS, CREATE_MODE);

        //print inside the txt due to its nbytes>0, with these seperate it due to error or not
        if(nbytes>0){
            dup2(fd, STDOUT_FILENO);
            printf("SUCCESS:\n");
            printf("%s", r_buf);
        }else{
            dup2(fd, STDOUT_FILENO);
            printf("FAIL:\n");
            printf("%s", r_buf2);
        };


        close(fd);

    }

    else {
        /**
         * This is the code for the child process.
         */

        /**
         * The child associates the read end of forward pipe (p2c) with its own stdin.
         */
        dup2(p2c[0], STDIN_FILENO);


        /**
         * The child associates the write end of reverse pipe (c2p) with its own stdout and stderr.
         */
        dup2(c2p[1], STDOUT_FILENO);   // send the answer of the blackbox to pipe
        dup2(xx[1], STDERR_FILENO);

        /**
         * The child can close all pipes since they are not needed anymore. Nothing will happen to stdin, stdout, stderr.
         */
        close(xx[0]);
        close(xx[1]);
        close(c2p[0]);
        close(c2p[1]);
        close(p2c[0]);
        close(p2c[1]);

        // exec blackbox with path
        char *source1;
        source1=argv[1];
        execlp(source1, "blackbox", NULL);





    }

    return(0);
}
