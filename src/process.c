#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>

void mysh_process_creation(int argc, char** argv){
	int pid;
	int status;
	pid = fork();

	if(pid == -1){
		fprintf(stderr, "fork() fails..\n");
	}
	else if(pid == 0){
		execv(argv[0], &argv[1]):
	}
	else{
		wait(&status);
	}
}
