#include "shell.h"

/**
 * pars_command - Extracts and returns the command from the input line.
 * @input: The line to be parsed.
 * Return: A pointer to the extracted command or NULL if not found.
 */
char *pars_command(char *input)
{
	char *command = NULL;
	int token_count;
	char **tokens;

	tokens = c_tokenize(input, " \t\n", &token_count);

	if (token_count > 0)
		command = strdup(tokens[0]);

	_free(tokens);

	return (command);
}

/**
 * _free - Frees memory allocated for an array of strings.
 * @arr: The array of strings to be freed.
 * Return: void
 */
void _free(char **arr)
{
	int i = 0;

	if (arr == NULL)
		return;

	for (i = 0; arr[i] != NULL; i++)
		free(arr[i]);

	free(arr);
}

/**
 * parse_arguments - Tokenizes the arguments from the input line.
 * @input: The input line to be parsed.
 * Return: A pointer to the token strings or NULL if no arguments found.
 */
char **parse_arguments(char *input)
{
	int token_count, i;
	char **tokens;
	char **args;

	tokens = c_tokenize(input, " \t\n", &token_count);

	if (token_count > 0)
	{
		args = malloc(sizeof(char *) * (token_count + 1));
		if (args == NULL)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
		for (i = 1; i < token_count; i++)
		{
			args[i - 1] = strdup(tokens[i]);
			if (args[i - 1] == NULL)
			{
				perror("./hsh");
				exit(EXIT_FAILURE);
			}
		}
		args[token_count - 1] = NULL;
		_free(tokens);
		return (args);
	}
	_free(tokens);
	return (NULL);
}
