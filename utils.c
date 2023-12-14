#include "shell.h"

/** comm_parser - determines entered the command
 * @command: command to parse
 * Return: constant matching the type of the command
 * Description -
 * 		 EXT_COMMANDS (1) i.e, /bin/ls
 * 		 PATH_COMMANDS (2) i.e, ls
 *		 INT_COMMANDS (3) i.e, exit, env
 *		 INVALID_COMMANDS (-1) invalid commands
 */

int comm_parser(char *command)
{
	int k;
	char *int_command[] = {"env", "exit", NULL};
	char *path = NULL;

	for (k = 0; command[k] != '\0'; k++)
	{
		if (command[k] == '/')
			return (EXT_COMMANDS);
	}
	for (k = 0; int_command[k] != NULL; k++)
	{
		if (_strcmp(command, int_command[k]) == 0)
			return (INT_COMMANDS);
	}
	path = check_path(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMANDS);
	}

	return (INVALID_COMMANDS);
}

/**
 * _getenv - A func that gets value of  env variable
 * @env_name: name of the environment variable
 * Return: pointer to value of env
 */
char *_getenv(char *env_name)
{
	char **env;
	char *temp_copy;
	char *pair_ptr;

	for (env = environment; *env != NULL; env++)
	{
		for (pair_ptr = *env, temp_copy = env_name;
		     *pair_ptr == *temp_copy; pair_ptr++, temp_copy++)
		{
			if (*pair_ptr == '=')
				break;
		}
		if ((*pair_ptr == '=') && (*temp_copy == '\0'))
			return (pair_ptr + 1);
	}
	return (NULL);
}

/**
 * exec_comm - A func that execs input command
 * @tokenized_command: tokenized form of the command (ls -l == {ls, -l, NULL})
 * @command_type: type of the command
 * Return: void
 */
void exec_comm(char **tok_command, int command_type)
{
	void (*func)(char **command);

	if (command_type == EXT_COMMANDS)
	{
		if (execve(tok_command[0], tok_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == PATH_COMMANDS)
	{
		if (execve(check_path(tok_command[0]), tok_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == INT_COMMANDS)
	{
		func = get_func(tok_command[0]);
		func(tok_command);
	}
	if (command_type == INVALID_COMMANDS)
	{
		print(name_of_shell, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tok_command[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * get_func - A func that gets function mapped to command
 * @command: string command to check
 * Return: pointer to the matching function, NULL on fail
 */
void (*get_func(char *command))(char **)
{
	int k;
	func_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (k = 0; k < 2; k++)
	{
		if (_strcmp(command, mapping[k].comm_name) == 0)
			return (mapping[k].func);
	}
	return (NULL);
}
