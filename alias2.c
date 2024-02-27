#include "shell.h"

/**
 * init_aliases - Initializes aliases if needed
 *
 * Return: Void
 */
void init_aliases(void)
{
	/* Define initial aliases here if needed */
}

/**
 * cleanup_aliases- Frees alias data
 *
 * Return: Void
 */
void cleanup_aliases(void)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		Alias *temp = current;

		current = current->next;
		free(temp);
	}
}

/**
 * alias_command - Handles the "alias" built-in command
 * @args: Array of command-line arguments
 *
 * This function processes the "alias" built-in command, allowing users
 * to define and list aliases for commands.
 *
 * Return: Void
 */

void alias_command(char **args)
{
	int i;
	char *name;
	char *value;

	if (args == NULL || args[0] == NULL)
	{
		list_aliases();
		return;
	}

	for (i = 0; args[i] != NULL; i++)
	{
		if (strstr(args[i], "=") != NULL)
		{
			name = strtok(args[i], "=");
			value = strtok(NULL, "=");
			define_alias(name, value);
		}
		else
		{
			print_alias(args[i]);
		}
	}
}
