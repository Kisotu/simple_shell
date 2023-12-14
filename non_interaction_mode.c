#include "shell.h"

/**
 * handle_non_interactive_mode - It handles non interactive mode
 * Return: void
 */
void handle_non_interactive_mode(void)
{
	size_t k = 0;
	char **curr_command = NULL;
	int i, type_command = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &k, stdin) != -1)
		{
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
		exit(status);
	}
}
