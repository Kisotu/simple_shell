#include "shell.h"

/**
 * quit - A fuction that exits the shell
 * @tok_command: command entered
 * Return: void
 */

void quit(char **tok_command)
{
	int num_of_tokens = 0, argum;

	for (; tok_command[num_of_tokens] != NULL; num_of_tokens++)
		;
	if (num_of_tokens == 1)
	{
		free(tok_command);
		free(line);
		free(commands);
		exit(status);
	}
	else if (num_of_tokens == 2)
	{
		argum = _atoi(tok_command[1]);
		if (argum == -1)
		{
			print(name_of_shell, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tok_command[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(tok_command);
			free(commands);
			exit(argum);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}

/**
 *env - A func that prints the current env
 *@tok_command: command entered
 *Return: void
 */
void env(char **tok_command __attribute__((unused)))
{
	int k;

	for (k = 0; environ[k] != NULL; k++)
	{
		print(environ[k], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}
