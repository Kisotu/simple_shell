#include "shell.h"

	int status = 0;
	char *name_of_shell = NULL;
	char *line = NULL;
	char **commands = NULL;

/**
 * main - the main shell code
 * @argc: arg count
 * @argv: arg vector
 * Return: 0 if success
 */
int main(int argc __attribute__((unused)), char **argv)
{
	size_t k = 0;
	int i;
	int type_command = 0;
	char **curr_command = NULL;

	signal(SIGINT, handle_ctrl_c);
	name_of_shell = argv[0];
	while (1)
	{
		handle_non_interactive_mode();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&line, &k, stdin) == -1)
		{
			free(line);
			exit(status);
		}
			rmv_ln(line);
			rmv_comment(line);
			commands = tokenize(line, ";");

		for (i = 0; commands[i] != NULL; i++)
		{
			curr_command = tokenize(commands[i], " ");
			if (curr_command[0] == NULL)
			{
				free(curr_command);
				break;
			}
			type_command = comm_parser(curr_command[0]);

			init(curr_command, type_command);
			free(curr_command);
		}
		free(commands);
	}
	free(line);

	return (status);
}
