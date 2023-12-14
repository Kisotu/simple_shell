#include "shell.h"

/**
 * init - starts the shell
 * @curr_command: checks if any command
 * @type_command: type of comm entered
 * Return: void
 */
void init(char **curr_command, int type_command)
{
	pid_t Process_ID;

	if (type_command == EXT_COMMANDS || type_command == PATH_COMMANDS)
	{
		Process_ID = fork();
		if (Process_ID == 0)
			exec_comm(curr_command, type_command);
		else
		{
			waitpid(Process_ID, &status, 0);
			status >>= 8;
		}
	}
	else
		exec_comm(curr_command, type_command);
}
