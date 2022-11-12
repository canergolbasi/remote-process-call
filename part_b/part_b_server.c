#include "add.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_APPEND)
#define CREATE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char **
add_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static char * result;
	static char * result3;

	int     p2c[2], c2p[2] , xx[2];  // for pipe, xx is need for detect error message of blaclbox
	pid_t   pid;
	static char w_buf[10000];
	static char r_buf[10000],r_buf2[10000];
	char final[10000]="SUCCESS:\n";  // then we add result value to these strings
	char final2[10000]="FAIL:\n";

	char input1[10000], input2[10000];

	int nbytes, nbytes2;

	pipe(p2c);
    pipe(c2p);
	pipe(xx);

	char *source1;
    source1=argp->p;


	if((pid=fork()) == -1) {     // if there is a error for fork
        fprintf(stderr, "fork() failed.\n");
        exit(-1);
    }
	if(pid>0){  // parent process
		char line[1000];

		close(p2c[0]);    // Parent will not read from p2c  // unused ones are closed
        close(c2p[1]);
		close(xx[1]);

		snprintf(input1,10000,"%d",argp->a); // convert to string
		snprintf(input2,10000,"%d",argp->b);

		strcat(input1," ");  // combine inputs
        strcat(input1,input2);
        strcat(input1,"\n");  // input1 like "10 20\n"

		write(p2c[1], input1, strlen(input1)); //wirite into p2c ant send it to p2c0


		nbytes = read(c2p[0], r_buf, sizeof(r_buf));
		nbytes2= read(xx[0], r_buf2, sizeof(r_buf2)); // for  detect error results


		if(nbytes>0){
			strcat(final,r_buf); //at the beginning final="SUCCESS\n", then we add r_buf

			result=(char *)malloc(strlen(final)+1);
			strcpy(result,final);   // copy final to result
		}else{
			strcat(final2,r_buf2);

			result=(char *)malloc(strlen(final2)+1);
			strcpy(result,final2);

		}

		memset(&(r_buf[0]),0,10000);
		memset(&(r_buf2[0]),0,10000);
		return &result;  // return result


	}else{
		//CHILD PROCESS


		dup2(p2c[0], STDIN_FILENO); // exec function taking input from pipe

		dup2(c2p[1], STDOUT_FILENO);   // capture output and error

		dup2(xx[1], STDERR_FILENO);

		// close unused ones anymore
		close(xx[0]);
        close(xx[1]);
		close(c2p[0]);
        close(c2p[1]);
        close(p2c[0]);
        close(p2c[1]);

        execlp(source1, "blackbox", NULL);  // exec blackbox




	}




}
