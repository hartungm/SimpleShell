#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	while(1)
	{
		char string[255];
		char *command, *token;
		char *params[255];
		int status;
		
		scanf("%s", &string);
		command = strtok(string, " ");
		token = strtok(NULL, " ");
		int i = 0;
		while(token != NULL)
		{
			params[i] = malloc(strlen(token) + 1);
			strcpy(params[i], token);
			token = strtok(NULL, " ");
			i++;
		}
		
		int pid = fork();
		if(pid < 0)
		{
			printf("Error in fork");
		}
		else if(pid) // Parent
		{
			waitpid(-1, &status, 0);
		}
		else // Child
		{
			execve(command, params, 0);
		}
	}
}