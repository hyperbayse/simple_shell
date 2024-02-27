#include "shell.h"

/**
 * print_built_ins - Prints and executes a specific built-in command
 * @command: the command to be executed
 * @argu: arguments associated with the command
 *
 * This function checks for and executes specific built-in commands.
 *
 * Return: 1 upon successful execution of the built-in command, else 0
 */

int print_built_ins(const char *command, char **argu)
{
	int count;

	builtin built_cmds[] = {
		{"env", handle_environment},
		{"setenv", handle_set_env},
		{"unsetenv", handle_unset_env},
		{"cd", handle_change_dir},
		{NULL, NULL}
	};

	for (count = 0; built_cmds[count].type != NULL; count++)
	{
		if (strcmp(built_cmds[count].type, command) == 0)
		{
			built_cmds[count].func(argu);
			return (1);
		}
	}
	return (0);
}

/**
 * handle_exit - Handles the exit command
 * @put_line: The command passed to the shell
 *
 * This function handles the exit command to terminate the shell.
 */
void handle_exit(char *put_line)
{
	free(put_line);
	exit(EXIT_SUCCESS);
}

/**
 * handle_environment - listing the environment variables
 * @args: the args pointer
 * Return: void
 */

void handle_environment(char **args)
{
	char **env = environ;
	(void)args;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * handle_set_env -  handles the set env commands
 * @args: handles the arguments
 * Return: void
 */
void handle_set_env(char **args)
{
	if (args == NULL || args[0] == NULL || args[1] == NULL)
		return;

	if (setenv(args[0], args[1], 1) == -1)
	{
		return;
	}
}

/**
 * handle_unset_env - handle the unset env command
 * @args: the arguments that is being passed
 * Return: void
 */
void handle_unset_env(char **args)
{
	if (args == NULL || args[0] == NULL)
		return;

	if (unsetenv(args[0]) == -1)
	{
		return;
	}
}
