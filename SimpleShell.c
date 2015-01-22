#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>

int main(int argc, char* argv [])
{
    
    
    
    
	while(1)
	{
		char string[1024];
		char *command;
		int status;
        pid_t pid;
        int childSwitches = 0, totalSwitches = 0;
        struct rusage usage;
        
        // Clock variable and time  -w
        clock_t start, end;
        double cpu_time_used;
        
        
        fputs("<Lab2>", stdout);
		fgets(string, 1024, stdin);
        if (strcmp(string, "quit\n") == 0){
            exit(0);
        }

        
        int size = 10;
        char** args = (char**) calloc(size, sizeof(char*) * size);
		command = strtok(string, " ");
        
        
		int i = 0;
		while(1)
		{
            if(i >=size ){
                size = size * 2;
                args = (char**) realloc(args, sizeof(char*) * size);
            }
			args[i] = malloc(sizeof(char) * strlen(command));
			strcpy(args[i], command);
			command = strtok(NULL, " ");
            //printf("%s", params[i]);
            //strtok(params[i], "\n");
			//printf("%s\n", params[i]);
			i++;
            if(!command){
                break;
            }
		}
        //removing the newline character
        args[i-1] = strtok(args[i-1], "\n");
        pid = fork();
        start = clock();
    
		if(pid < 0)
		{
			perror("Error in fork");
            exit(1);
		}
		else if(pid) // Parent
		{
            wait(&status);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("%s", "Time used for child: ");
            printf("%f seconds\n", cpu_time_used);
            getrusage(RUSAGE_CHILDREN, &usage);
            totalSwitches = usage.ru_nivcsw;
            printf("%d contact switches made\n", totalSwitches-childSwitches);
            childSwitches = totalSwitches;
		}
		else // Child
		{
            if (execvp(*args, args)<0){
                perror("execution of child failed");
                exit(1);
            }
            return 0;
		}
	}
    return 0;
}