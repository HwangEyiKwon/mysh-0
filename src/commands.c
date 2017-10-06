#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio_ext.h>

#include "commands.h"

#define BUFFER_SIZE 255

int do_cd(int argc, char** argv) {
  if (!validate_cd_argv(argc, argv))
    return -1;
  const char* path;
  if(!strcmp(argv[1], "~"))
	path = "/home/aeis";
  else
	path = argv[1];
  printf("%s", path);
  chdir(path);
  printf("cd did\n");
  return 0;
}

int do_pwd(int argc, char** argv) {
  if (!validate_pwd_argv(argc, argv))
    return -1;
  char buffer[BUFFER_SIZE];
  int buffer_size = 255;
  getcwd(buffer, buffer_size);
  printf("%s\n",buffer);
  //__fpurge((FILE*)buffer);
  //free(buffer);
  printf("pwd did\n");
  return 0;
}

int validate_cd_argv(int argc, char** argv) {
  if(argc != 2 || (strcmp(argv[0], "cd")))
	return 0;
  return 1;
}

int validate_pwd_argv(int argc, char** argv) {
  printf("%s, %d\n",argv[0], argc);
  if(argc != 1 || (strcmp(argv[0], "pwd")))
	return 0;
  return 1;
}
/*
int main() {
  int a = 1;
  char* b[2];
//  b = (char**) calloc(2, sizeof(char*));
//  b[0] = (char*) calloc(3, sizeof(char));
//  b[1] = (char*) calloc(3, sizeof(char));
  
  b[0] = "cd";
  b[1] = "..";
  do_pwd(a, b);
  do_cd(a, b);
  do_pwd(a,b);
}*/
