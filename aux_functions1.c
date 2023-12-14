#include "shell.h"

/**
 * print - A function that prints a string to STDOUT
 * @str: string to print
 * @stream: stream to print to
 * Return: void, return nothing
 */
void print(char *str, int stream)
{
	int k = 0;

	for (; str[k] != '\0'; k++)
		write(stream, &str[k], 1);
}

/**
 * rmv_ln - A function that removes new line
 * @str: string to use 
 * Return: void
 */
void remove_newline(char *str)
{
	int k = 0;

	while (str[k] != '\0')
	{
		if (str[k] == '\n')
			break;
		k++;
	}
	str[k] = '\0';
}

/**
 * _strlen - counts string length
 * @string: string to be counted
 * Return: length of the string
 */
int _strlength(char *str)
{
	int length = 0;

	if (str == NULL)
		return (length);
	for (; str[length] != '\0'; length++)
		;
	return (length);
}

/**
 * _strcopy - A func that copies a string to a buffer
 * @src: source string
 * @dest: destination string
 * Return: void
 */
void _strcopy(char *src, char *dest)
{
	int k = 0;

	for (; src[k] != '\0'; k++)
		dest[k] = src[k];
	dest[k] = '\0';
}

