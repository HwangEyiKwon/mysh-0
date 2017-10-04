#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void mysh_parse_command(const char* command,
                        int *argc, char*** argv)
{
	char* command_temp = (char*) command;
	char* command_token;
	int command_token_len;
	int string_num = 1;	
	char* strptr;
	(*argc) = 0;

	strptr = strchr(command_temp, ' ');/*
	//there is only blank ex)"\t" " " "\n"
	if(!strtok(command_temp, " \t\n")){
		*argv = (char**)calloc(1, sizeof(char*));
                *argc = 1;
                (*argv)[0] = (char*)calloc(1, sizeof(char));
                (*argv)[0] = NULL;
		printf("fucking goood\n");
	}*/
	//there is only one string ex) pwd
	if(strptr == NULL){
		command_token = strtok(command_temp, "\n");
		command_token_len = strlen(command_token);
		*argv = (char**)calloc(string_num, sizeof(char*));
		(*argv)[0] = (char*)calloc((command_token_len + 1), sizeof(char));
		(*argc) = 1;
		strcpy((*argv)[0], command_temp);	
	}
	else{
		while(strptr != NULL){
			string_num++;
			strptr = strchr(strptr+1, ' ');
		}
		command_token = strtok(command_temp, " \t\n");
		*argv = (char**)calloc(string_num, sizeof(char*));
		for(int i = 0; command_token != NULL; i++){
			command_token_len = strlen(command_token);
			(*argc)++;
			(*argv)[i] = (char*)calloc((command_token_len + 1), sizeof(char));
			strcpy((*argv)[i], command_token);
			command_token = strtok(NULL, " \t\n");	
			printf("%s, The %dth.\n", (*argv)[i], *argc);
		}
	}
	printf("SUCCESS!\n");
}
/*
int main(){
	const char str[] = "cd test hwang";
	int a;
	char** b;

	mysh_parse_command(str, &a, &b);
	return 0;
}*/
