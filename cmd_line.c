#include "shell.h"

/**
 * handle_cmd_line - Handles the command line input
 * @lineinput: The input command line
 *
 * This function processes a command line input, parses it, and executes
 * individual commands or handles logical operators.
 */
void handle_cmd_line(char *lineinput)
{
	char *command, **args, **tokens, *token;
	int i, j = 0;

	if (lineinput == NULL || lineinput[0] == '\0' || is_whitespace(lineinput))
	{
		return;
	}

	lineinput = remove_comment(lineinput);

	tokens = c_tokenize(strtrim(lineinput), ";", &j);

	for (i = 0; i < j; i++)
	{
		token = tokens[i];

		if (strstr(token, "&&") || strstr(token, "||"))
		{
			handle_logical_operator(token);
		}
		else
		{
			command = pars_command(token);
			args = parse_arguments(token);

			execute_all_command(command, args);

			if (args != NULL)
				_free(args);
			free(command);
		}
	}
	_free(tokens);
}

/**
 * is_whitespace - Checks if a string contains only whitespace characters
 * @str: The input string
 * Return: 1 if the string contains only whitespace, 0 otherwise
 */
int is_whitespace(const char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t' || *str == '\n' ||
				*str == '\r' || *str == '\f' || *str == '\v')
		{
			str++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}
