#include "shell.h"

/**
 * process_script_file - Process commands from a script file.
 * @filename: The name of the script file.
 * Returns: Nothing.
 */
void process_script_file(const char *filename)
{
	FILE *script_file = fopen(filename, "r");
	char *input_line;
	size_t input_line_size;
	ssize_t bytes_read;

	if (script_file == NULL)
	{
		fprintf(stderr, "%s: 0: Can't open %s\n", "./hsh", filename);
		exit(1);
	}

	input_line = NULL;
	input_line_size = 0;

	while ((bytes_read = getline(&input_line,
					&input_line_size, script_file)) != -1)
	{
		handle_cmd_line(input_line);
		free(input_line);
	}
	fclose(script_file);
	free(input_line);
}

/**
 * process_unatty_input - Process input in non-interactive or non-isatty mode.
 * @input_line: The input line to be processed.
 * Returns: Nothing.
 */

void process_unatty_input(char *input_line)
{
	if (beginwith(input_line, "exit"))
		handle_exit(input_line);
	else
		handle_cmd_line(input_line);
}
