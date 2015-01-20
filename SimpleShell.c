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
		
		fgets(string, sizeof(string), stdin);
		command = malloc(sizeof(string) + 1);
		command = strtok(string, " ");
		token = strtok(NULL, " ");
		printf("%s\n", command);
		int i = 0;
		while(token != NULL)
		{
			params[i] = malloc(sizeof(token) + 1);
			strcpy(params[i], token);
			token = strtok(NULL, " ");
			printf("%s\n", params[i]);
			i++;
		}
		
		int pid = fork();
		if(pid < 0)
		{
			printf("Error in fork");
		}
		else if(pid) // Parent
		{
			printf("%s\n", "Parent Waiting... ");
			waitpid(-1, &status, 0);
		}
		else // Child
		{
			printf("%s\n", "Child Begins... ");
			execve(command, params, 0);
		}
	}
}