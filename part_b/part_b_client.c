#include "add.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_APPEND)
#define CREATE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


char *outputtxt_path;

void
add_prog_1(char *host, int x, int y ,char *blackbox_path)  // add extra blackbox path
{
	CLIENT *clnt;
	char * *result_1;
	numbers  add_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, ADD_PROG, ADD_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	add_1_arg.a=x;   // number 1
	add_1_arg.b=y;	// number 2
	strcpy(add_1_arg.p,blackbox_path); // path information for blackbox

	result_1 = add_1(&add_1_arg, clnt);

	if (result_1 == (char **) NULL) {  // if the result is null
		clnt_perror (clnt, "call failed");
	}else{
		int fd;
		fd=open(outputtxt_path, CREATE_FLAGS, CREATE_MODE);

		dup2(fd, STDOUT_FILENO);  // printf -write in txt

		printf("%s",*result_1);

        close(fd);


	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	char *blackbox_path;

	if (argc < 4) { // if the entered argument less than 4
		printf ("usage: %s blackbox_path txt_path server_host\n", argv[0]);
		exit (1);
	}

	blackbox_path=argv[1];
	outputtxt_path=argv[2];
	host = argv[3];

	int firstnumber,secondnumber;
	scanf("%d",&firstnumber);
	scanf("%d",&secondnumber);

	add_prog_1 (host, firstnumber ,secondnumber,blackbox_path);

exit (0);
}
