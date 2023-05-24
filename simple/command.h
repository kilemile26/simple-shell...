#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

#define MAX_COMMAND_LENGTH 1024

void execute_command(char *command);
void display_prompt(void);
int isExitCommand(const char* command);
bool find_path(const char *command, char *command_path, char *path);

#endif
