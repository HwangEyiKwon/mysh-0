#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NUMBER 100

void mysh_parse_command(const char* command,
                        int *argc, char*** argv)
{
	char* command_temp;			//it is used for conservation of "command"
	char* command_token;			//it is used for token of "command_temp"
	int command_token_len;			//it is used for (char*)calloc
	int string_num = 1;			//it is used for (char**)calloc
	char* strptr;				//it is used for finding " ", determination of one string
	int i;
	
	command_temp = (char*)calloc(MAX_NUMBER, sizeof(char));
	strcpy(command_temp, command);
	(*argc) = 0;
	
	strptr = strchr(command_temp, ' ');	// it is used for (char**)calloc, determination of one string
	//it trims whitespace
	while(isspace(*command_temp)) 
		command_temp++;
	//there is only blank ex)"\t" " " "\n"
	if(*command_temp == 0){
		*argv = (char**)calloc(1, sizeof(char*));
                *argc = 1;
                (*argv)[0] = (char*)calloc(1, sizeof(char));
	}
	//there is only one string. ex) pwd
	else if(strptr == NULL){
		command_token = strtok(command_temp, "\n");	//it trims "\n"
		command_token_len = strlen(command_token);
		*argv = (char**)calloc(string_num, sizeof(char*));
		(*argv)[0] = (char*)calloc((command_token_len + 1), sizeof(char));
		(*argv)[1] = (char*)calloc(1, sizeof(char));
		(*argc) = 1;
		strcpy((*argv)[0], command_temp);
		//strcpy((*argv)[1], NULL);
		//printf("%s", (*argv)[1]);
	}
	//there are some strings ex)cd src / cd .. / cd ./home/aeis
	else{
		//it counts the number of string
		while(strptr != NULL){
			string_num++;
			strptr = strchr(strptr+1, ' ');
		}
		//below commands: make token and assign to argv
		command_token = strtok(command_temp, " \t\n");
		*argv = (char**)calloc(string_num, sizeof(char*));
		for(i = 0; command_token != NULL; i++){
			command_token_len = strlen(command_token);
			(*argc)++;
			(*argv)[i] = (char*)calloc((command_token_len + 1), sizeof(char));
			strcpy((*argv)[i], command_token);
			command_token = strtok(NULL, " \t\n");
		}
		(*argv)[i] = (char*)calloc(1, sizeof(char));
	}
}
