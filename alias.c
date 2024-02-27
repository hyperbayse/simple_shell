#include "shell.h"

/* external vriable*/
Alias *alias_list = NULL;

/**
 * define_alias - Defines an alias for a command
 * @name: The name of the alias
 * @value: The value of the alias
 *
 * This function defines an alias for a command by creating an Alias struct
 * and adding it to the linked list of aliases.
 *
 * @name: The name of the alias.
 * @value: The value of the alias.
 */
void define_alias(const char *name, const char *value)
{
	Alias *alias = (Alias *)malloc(sizeof(Alias));

	if (alias == NULL)
	{
		fprintf(stderr, "Error: Failed to allocate memory for alias.\n");
		return;
	}
	strncpy(alias->name, name, sizeof(alias->name));
	strncpy(alias->value, value, sizeof(alias->value));
	alias->next = alias_list;
	alias_list = alias;
}

/**
 * list_aliases - Lists all defined aliases
 *
 * This function lists all defined aliases, printing each alias in the form
 * "alias name='value'" one per line.
 */
void list_aliases(void)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		printf("alias %s='%s'\n", current->name, current->value);
		current = current->next;
	}
}

/**
 * print_alias - Prints the value of a specific alias
 * @name: The name of the alias to print
 *
 * This function prints the value of a specific alias with the given name
 * in the form "alias name='value'".
 *
 * @name: The name of the alias to print.
 */
void print_alias(const char *name)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			printf("alias %s='%s'\n", current->name, current->value);
			return;
		}
		current = current->next;
	}
	fprintf(stderr, "Alias '%s' not found.\n", name);
}
