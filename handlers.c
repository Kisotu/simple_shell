#include "shell.h"

/**
 * _atoi -A func that converts string to integer
 * @s: the string to convert
 * Return: the converted int
 */
int _atoi(char *s)
{
	unsigned int k = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0'  && *s <= '9')
			k = (k * 10) + (*s - '0');
		else if (k > 0)
			break;
	} while (*s++);
	return (k);
}

/**
 * _mem_realloc - A func that reallocates a memory
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @prev: size of mem of ptr
 * @curr: size of the new memory to allocate
 * Return: pointer to the address of the new memory allocated
 */
void *_mem_realloc(void *ptr, unsigned int prev, unsigned int curr)
{
	void *temp;
	unsigned int k;

	if (ptr == NULL)
	{
		temp = malloc(curr);
		return (temp);
	}
	else if (curr == prev)
		return (ptr);
	else if (curr == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		temp = malloc(curr);
		if (temp != NULL)
		{
			for (k = 0; k < min(prev, curr); k++)
				*((char *)temp + k) = *((char *)ptr + k);
			free(ptr);
			return (temp);
		}
		else
			return (NULL);

	}
}

/**
 * rmv_comment - A func that remove everything after the '#' symbol
 * @input_str: str to use
 * Return: void
 */
void rmv_comment(char *input_str)
{
	int k = 0;

	if (input_str[k] == '#')
		input_str[k] = '\0';
	while (input_str[k] != '\0')
	{
		if (input_str[k] == '#' && input_str[k - 1] == ' ')
			break;
		k++;
	}
	input_str[k] = '\0';
}

/**
 * handle_ctrl_c - handles the signal raised by CTRL-C
 * @sign_no: signal number
 * Return: void
 */
void handle_ctrl_c(int sign_no)
{
	if (sign_no == SIGINT)
		print("\n($) ", STDIN_FILENO);
}
