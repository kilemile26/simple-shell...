#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtins.h"

void execute_builtin(char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(command, "env") == 0)
	{
		char **env;
		extern char **environ;

		for (env = environ; *env != NULL; env++)
		{
			printf("%s\n", *env);
		}
	}
	else
	{
		printf("Command not found: %s\n", command);
	}
}
