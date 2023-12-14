#include "shell.h"

/**
 * _strcmp - A func that compares two strings
 * @s1: first string
 * @s2: second string
 * Return: difference of the two strings
 */
int _strcmp(char *s1, char *s2)
{
	int k = 0;

	while (s1[k] != '\0')
	{
		if (s1[k] != s2[k])
			break;
		k++;
	}
	return (s1[k] - s2[k]);
}

/**
 * _strspn -A func that gets the length of substring prefix
 * @s1: string to search
 * @s2: string to use
 * Return: number of bytes in the initial segment
 */

int _strspn(char *s1, char *s2)
{
	int k = 0;
	int match_no = 0;

	while (s1[k] != '\0')
	{
		if (_strchr(s2, (char)s1[k]) == NULL)
			break;
		match_no++;
		k++;
	}
	return (match_no);
}

/**
 * _strcspn - A func that computes segment of s1 which
 * consists of characters not in s2
 * @s1: string to search
 * @s2: string to use
 * Return: index at which a char in s1 exists in s2
 */
int _strcspn(char *s1, char *s2)
{
	int length = 0, k;

	for (k = 0; s1[k] != '\0'; k++)
	{
		if (_strchr(s2, s1[k]) != NULL)
			break;
		length++;
	}
	return (length);
}
