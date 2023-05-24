#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

/**
 * execute_builtin - function for builtin commands
 *
 */

void execute_builtin(char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(command, "env") == 0)
	{
		extern char **environ;
		char **env = environ;

		for (; *env != NULL; env++)
		{
			printf("%s\n", *env);
		}
	}
	else
	{
		printf("Command not found: %s\n", command);
	}
}
