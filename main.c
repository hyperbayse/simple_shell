#include "shell.h"

/**
 * main - Entry point of the shell program
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on successful execution
 */
int main(int ac, char *av[])
{
	if (is_interactive_mode(ac))
	{
		interactive_mode();
	} else
	{
		non_interactive_mode(ac, av);
	}

	return (0);
}

/**
 * is_interactive_mode - Checks if the program is in interactive mode
 * @ac: Argument count
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */

int is_interactive_mode(int ac)
{
	return (isatty(STDIN_FILENO) && ac == 1);
}

/**
 * interactive_mode - Handles the interactive mode of the shell
 *
 * Return: void
 */
void interactive_mode(void)
{
	char *in_line;

	while (1)
	{
		display_prompt();
		in_line = c_getline();

		if (in_line == NULL)
		{
			printf("\n");
			break;
		}

		process_input(in_line);
		free(in_line);
	}
}

/**
 * non_interactive_mode - Handles the non-interactive mode of the shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: void
 */
void non_interactive_mode(int ac, char *av[])
{
	char *in_line = NULL;
	size_t in_line_size = 0;

	if (ac == 2)
	{
		process_script_file(av[1]);
	} else
	{
		while (getline(&in_line, &in_line_size, stdin) != -1)
		{
			process_unatty_input(in_line);
		}
		free(in_line);
	}
}

/**
 * process_input - Process the user input in the shell
 * @input: User input string
 *
 * Return: void
 */
void process_input(char *input)
{
	char **alias_args;

	if (beginwith(input, "alias"))
	{
		alias_args = parse_arguments(input);
		alias_command(alias_args);
		_free(alias_args);
	}
	else if (beginwith(input, "exit"))
	{
		handle_exit(input);
	}
	else
	{
		handle_cmd_line(input);
	}
}
