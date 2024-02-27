#include "shell.h"

/**
 * handle_logical_operator - Handle logical operators in a command line.
 * @cmdline: The input line containing operators.
 * Return: The status of the operation.
 */
int handle_logical_operator(char *cmdline)
{
	char **tokens = NULL, *operators;
	int i, count = 0, status = 0;
	int executeRightSide = 1;

	operators = store_operators(cmdline);
	tokens = c_tokenize(cmdline, "&&||", &count);
	for (i = 0; i < count; i++)
	{
		if (operators[i] == 38)
		{
			execute_operator(tokens[i], &status);
			if (status != 0)
			{
				free(operators);
				_free(tokens);
				return (0);
			}
		}
		else if (operators[i] == 124)
		{
			if (executeRightSide)
			{
				execute_operator(tokens[i], &status);
				executeRightSide = (status != 0);
			}
		}
	}
	_free(tokens);
	free(operators);
	return (1);
}

/**
 * execute_operator - Execute a command with logical operators.
 * @cmd: The command to execute.
 * @status: A pointer to store the execution status.
 * Return: The status of the execution.
 */

int execute_operator(char *cmd, int *status)
{
	char **args, *command;
	int cmd_result;

	command = pars_command(cmd);
	args = parse_arguments(cmd);
	cmd_result = execute_all_command(command, args);

	if (WIFEXITED(cmd_result))
	{
		*status = WEXITSTATUS(cmd_result);
		return (1);
	}
	*status = 0;
	_free(args);
	free(command);
	return (0);
}

/**
 * store_operators - Extract and store logical operators from a command line.
 * @cmd: The command line.
 * Return: An array of the operators.
 */

char *store_operators(char *cmd)
{
	int cmdLength = strlen(cmd);
	int i = 0, c = 0;
	char *operators = (char *)malloc(cmdLength * sizeof(char));

	while (i < cmdLength)
	{
		if (cmd[i] == '&' || cmd[i] == '|')
		{
			operators[c++] = cmd[i];
			i++;
			if (cmd[i] == cmd[i - 1])
			{
				operators[c++] = cmd[i];
				i++;
			}
		}
		else
			i++;
	}
	return (operators);
}
