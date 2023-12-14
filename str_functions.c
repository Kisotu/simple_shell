#include "shell.h"

/**
 *_strconcat - A func that concatenates two strings
 *@dest: destination string
 *@src:  source string
 * Return: address of the new string
 */

char *_strconcat(char *dest, char *src)
{
	char *str =  NULL;
	int src_length = _strlength(src);
	int dest_length = _strlength(dest);

	str = malloc(sizeof(*str) * (dest_length + src_length + 1));
	_strcopy(dest, str);
	_strcopy(src, str + dest_length);
	str[dest_length + src_length] = '\0';

	return (str);
}

/**
 *_strchr - A func that finds a character in a string
 *@str: string to search
 *@c: char to check
 *Return: pointer to the first occurence of c in s
 */

char *_strchr(char *str, char c)
{
	int k = 0;

	for (; str[k] != c && str[k] != '\0'; k++)
		;
	if (str[k] == c)
		return (str + k);
	else
		return (NULL);
}

/**
 *tokenize -A func that tokenizes input and stores it into an array
 *@str: input string to tokenize
 *@delim: delimiter to use
 *Return: an array of tokens
 */

char **tokenize(char *str, char *delim)
{
	char *ptr_save;
	int num_delim = 0;
	char **av = NULL;
	char *token = NULL;

	token = _strtok_r(str, delim, &ptr_save);

	while (token != NULL)
	{
		av = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
		av[num_delim] = token;
		token = _strtok_r(NULL, delim, &ptr_save);
		num_delim++;
	}

	av = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
	av[num_delim] = NULL;

	return (av);
}

/**
 *_strtok_r - A func that tokenizes a string
 *@str: string to tokenize
 *@delim: delimiter to use
 *@ptr_save: pointer to the next token
 *Return: Next available token
 */
char *_strtok_r(char *str, char *delim, char **ptr_save)
{
	char *fin;

	if (str == NULL)
		str = *ptr_save;

	if (*str == '\0')
	{
		*ptr_save = str;
		return (NULL);
	}

	str += _strspn(str, delim);
	if (*str == '\0')
	{
		*ptr_save = str;
		return (NULL);
	}

	fin = str + _strcspn(str, delim);
	if (*fin == '\0')
	{
		*ptr_save = fin;
		return (str);
	}

	*fin = '\0';
	*ptr_save = fin + 1;
	return (str);
}

/**
 * check_path - A func that checks if command is found in the PATH
 * @command: command to check
 * Return: Path of command, NULL if not found
 */
char *check_path(char *command)
{
	int k;
	char *path = _getenv("PATH");
	char **path_arr = NULL;
	char *path_copy;
	char *temp, *temp2;

	if (path == NULL || _strlength(path) == 0)
		return (NULL);
	path_copy = malloc(sizeof(*path_copy) * (_strlength(path) + 1));
	_strcopy(path, path_copy);
	path_arr = tokenize(path_copy, ":");
	for (k = 0; path_arr[k] != NULL; k++)
	{
		temp2 = _strconcat(path_arr[k], "/");
		temp = _strconcat(temp2, command);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_arr);
			free(path_copy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_copy);
	free(path_arr);
	return (NULL);
}

