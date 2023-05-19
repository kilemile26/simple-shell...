#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "command.h"
#include "builtins.h"

void execute_command(char *command)
{
	pid_t pid;
	int status;
	extern char **environ;

	char ** argv = malloc(2 * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		argv[0] = command;
		argv [1] = NULL;
		execve(command, argv, environ);
		
		/* If execve returns, an error occurred */
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}
	else
	{
		/* Fork failed */
		perror("fork");
	}
}
