#include "shell.h"

/**
 * c_tokenize - Custom tokenization function.
 * @input: The input string to be tokenized.
 * @delimiters: The delimiters used for tokenization.
 * @token_count: Pointer to the token count.
 *
 * Return: An array of pointers to tokens.
 */

char **c_tokenize(char *input, const char *delimiters, int *token_count)
{
	char **tokens = NULL, *token, *input_copy, **temp;
	int count = 0, i;

	if (input == NULL || delimiters == NULL)
		return (NULL);
	input_copy = strdup(input);
	if (input_copy == NULL)
	{
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	token = strtok(input_copy, delimiters);
	while (token != NULL)
	{
		temp = realloc(tokens, (count + 2) * sizeof(char *));
		if (temp == NULL)
		{
			perror("./hsh");
			for (i = 0; i < count; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
			exit(EXIT_FAILURE);
		}
		tokens = temp;
		tokens[count] = strdup(token);
		if (tokens[count] == NULL)
		{
			perror("./hsh");
			for (i = 0; i < count; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
			exit(EXIT_FAILURE);
		}
		count++;
		token = strtok(NULL, delimiters);
	}

	free(input_copy);
	tokens[count] = NULL;
	*token_count = count;
	return (tokens);
}

/**
 * c_tokenizer - Custom tokenizing function.
 * @str: The input string to be tokenized.
 * @delimiters: The delimiters used for tokenization.
 *
 * Return: A pointer to the next token.
 */
char *c_tokenizer(char *str, const char *delimiters)
{
	static char *saved_str;
	char *token = NULL;

	if (str != NULL)
		saved_str = str;

	if (saved_str == NULL || *saved_str == '\0')
		return (NULL);

	token = saved_str;

	while (*saved_str != '\0' && strchr(delimiters, *saved_str) == NULL)
		saved_str++;

	if (*saved_str != '\0')
	{
		*saved_str = '\0';
		saved_str++;
	}
	return (token);
}
