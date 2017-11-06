#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "commands.h"

#define BUFFER_SIZE 255

int do_cd(int argc, char** argv) {
  if (!validate_cd_argv(argc, argv))
    return -1;
  const char* path;
  //if argv[1] is "~" -> change path to home directory, because "~" is not realized
  if(!strcmp(argv[1], "~"))
	path = "/home/aeis";
  else
	path = argv[1];
  //Unix system call chdir: change working directory
  chdir(path);
  return 0;
}

int do_pwd(int argc, char** argv) {
  if (!validate_pwd_argv(argc, argv))
    return -1;
  char buffer[BUFFER_SIZE];
  int buffer_size = 255;
  //Unix system call getcwd: get current directory
  getcwd(buffer, buffer_size);
  printf("%s\n",buffer);
  return 0;
}

int validate_cd_argv(int argc, char** argv) {
  int return_stat;
  char* directory_name;
  struct stat directory_info;
  mode_t directory_mode;
  //check if command is "cd ***" or not
  if(argc != 2 || (strcmp(argv[0], "cd")))
	return 0;
  directory_name = argv[1];
  //check if 'directory_name' dosen't exist, "~" is exception
  //Unix system call stat: get file status
  if((return_stat = stat(directory_name, &directory_info)) == -1 && strcmp(directory_name, "~")){
	printf("%s: not exist such directory\n",directory_name);
	return 0;
  }
  directory_mode = directory_info.st_mode;
  //check if 'directory_name' is not a directory, is a file
  if(S_ISREG(directory_mode)){
	printf("%s: is not a directory\n",directory_name);
 	return 0;
  }
  return 1;
}

int validate_pwd_argv(int argc, char** argv) {
  //check if command is "pwd" or not
  if(argc != 1 || (strcmp(argv[0], "pwd")))
	return 0;
  return 1;
}

void mysh_process_creation(int argc, char** argv){
	int pid;
	int status;
	pid = fork();
	char* token;
	char* path = argv[0];

	token = strrchr(argv[0], '/') + 1;
	char* arr[] = {token, argv[1], NULL};

	if(pid == -1){
		fprintf(stderr, "fork() fails..\n");
	}
	else if(pid == 0){
		if(argc == 1){
			execv(path, &argv[1]);
		}
		else{
			execv(path, arr);
		}
	}
	else{
		wait(&status);
	}
}






