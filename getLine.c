#include "shell.h"

/**
 * c_getline - Custom getline function
 *
 * This function reads a line of text from the standard input.
 *
 * Return: A pointer to the read line or NULL on failure.
 */
char *c_getline(void)
{
	char *line_input = NULL;
	size_t line_size = 0;
	ssize_t line_length = getline(&line_input, &line_size, stdin);

	if (line_length == -1)
	{
		perror("./hsh");
		free(line_input);
		return (NULL);
	}

	if (line_length > 0)
	{
		if (line_input[line_length - 1] == '\n')
		{
			line_input[line_length - 1] = '\0';
		}
	}
	return (line_input);
}

/**
 * _getline - Custom getline function with provided stream
 *
 * @linept: Pointer to the allocated buffer for the line.
 * @n: Pointer to the size of the allocated buffer.
 * @stream: The stream to read from.
 *
 * Return: The number of characters read or -1 on failure.
 */
ssize_t _getline(char **linept, size_t *n, FILE *stream)
{
	char *line = NULL, *new_line;
	size_t size = 0;
	int c;
	ssize_t len = 0;

	if (linept == NULL || n == NULL || stream == NULL)
		return (-1);
	while ((c = fgetc(stream)) != EOF)
	{
		if (len >= (ssize_t)(size - 1))
		{
			size = (size == 0) ? 128 : size * 2;
			new_line = (char *)realloc(line, size);
			if (new_line == NULL)
			{
				free(line);
				return (-1);
			}
			line = new_line;
		}
		line[len] = (char)c;
		len++;
		if (c == '\n')
			break;
	}
		if (len > 0)
	{
		line[len] = '\0';
		*linept = line;
		*n = size;
	}
	else
	{
		free(line);
		*linept = NULL;
		*n = 0;
		return (-1);
	}
	return (len);
}

/**
 * remove_comment - Remove comments from a line
 *
 * @line: The input line, which may contain a comment.
 *
 * Return: A pointer to the line with the comment removed.
 */
char *remove_comment(char *line)
{
	char *comment = strchr(line, '#');

	if (line == NULL)
		return (NULL);
	if (comment != NULL)
	{
		*comment = '\0';
	}
	return (line);
}
