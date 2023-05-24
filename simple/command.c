#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "command.h"
#include "builtins.h"

/**
 * find_path - check if the command exists in the PATH directories.
 *
 * @command: The command to check.
 * @command_path: Pointer to a buffer to store the full path of the command.
 * @path: The PATH environment variable.
 *
 * Return: true if the command is found, false otherwise.
 */

bool find_path(const char *command, char *command_path, char *path)
{
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		sprintf(command_path, "%s/%s", token, command);
		if (access(command_path, X_OK) == 0)
		{
			return (true);
		}
		token = strtok(NULL, ":");
	}
	return (false);
}

/**
 * isExitCommand - function for exiting on command exit
 * @command: pointer to exit command
 *
 * Return: 1 on success, 0 otherwise
 */

int isExitCommand(const char* command)
{
	if (strcmp(command, "exit") == 0)
	{
		return 1;
	} else {
		return 0;
	}
}

/**
 * execute_command - funtion for executing commands in shell
 * @command: command The command to execute.
 *
 * Return: The exit status of the command.
 */

void execute_command(char *command)
{
	pid_t pid;
	char *path;
	char *command_path;

	/* ignore empty command */
	if (command == NULL || strlen(command) == 0)
	{
		return;
	}
	/* Check if the command exists in the PATH */

	path = getenv("PATH");

	if (!find_path(command, command_path, path))
	{
		fprintf(stderr, "Commandnot found: %s\n", command);
		return;
	}
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		char *command_path = malloc(MAX_COMMAND_LENGTH * sizeof(char));
		char *argv[] = { command_path, NULL };

		if (command_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		if (execve(command_path, argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		free(command_path);
	} else {
		int status;

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
	return;
}
