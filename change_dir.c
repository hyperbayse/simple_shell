#include "shell.h"

/**
 * change_directory - Change the current directory based on the given path.
 * @new_d: The new directory path.
 * Return: 0 on success, -1 on failure.
 */
int change_directory(char *new_d)
{
	if (new_d == NULL)
	{
		perror("./hsh");
		return (-1);
	}

	if (chdir(new_d) != 0)
	{
		if (errno == EACCES)
		{
			fprintf(stderr, "cd: Permission denied: %s\n", new_d);
		}
		else if (errno == ENOENT)
		{
			fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", new_d);
		}
		else
		{
			perror("./hsh");
		}
		return (-1);
	}

	return (0);
}

/**
 * handle_change_dir - handle the change directory command
 * @args: the argument
 * Return: void
 */
void handle_change_dir(char **args)
{
	char *new_d;
	char *full_new_d;
	char *current_d;

	if (args == NULL || args[0] == NULL)
		new_d = getenv("HOME");
	else if (strcmp(args[0], "-") == 0)
		new_d = getenv("OLDPWD");
	else
		new_d = args[0];

	current_d = getcwd(NULL, 0);
	if (current_d == NULL)
	{
		perror("./hsh");
		return;
	}

	if (change_directory(new_d) == 0)
	{
		full_new_d = getcwd(NULL, 0);
		if (setenv("PWD", full_new_d, 1) != 0)
		{
			perror("./hsh");
		}

		if (setenv("OLDPWD", current_d, 1) != 0)
		{
			perror("./hsh");
		}

		free(full_new_d);
	}

	free(current_d);
}
