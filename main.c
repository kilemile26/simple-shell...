#include <stdio.h>
#include <stdlib.h>
#include "prompt.h"
#include "command.h"

/**
 * main - main programm
 * Return: success
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		display_prompt();
		if (fgets(command, sizeof(command), stdin) == NULL)
			break;  /* Handle end of file (Ctrl+D) */

		/* Remove trailing newline character */
		command[strcspn(command, "\n")] = '\0';
		execute_command(command);
	}
	return (EXIT_SUCCESS);
}
