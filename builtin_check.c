#include "shell.h"

const char *builtin_cmds[] = {
	"cd",
	"alias",
	"setenv",
	"unsetenv",
	"env",
	"exit",
	NULL
};

/**
 * its_builtin_cmd - Checks if the command is a built-in command.
 * @cmd: The passed command.
 * Return: 1 if it is a built-in command, 0 if it's not.
 */
int its_builtin_cmd(const char *cmd)
{
	int counter = 0;

	while (builtin_cmds[counter] != NULL)
	{
		if (strcmp(cmd, builtin_cmds[counter]) == 0)
		{
			return (1);
		}
		counter++;
	}
	return (0);
}
