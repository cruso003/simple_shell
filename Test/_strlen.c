#include "shell.h"

/**
 * _strlen - a function that returns the length of a string
 * @s:- pointer string
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int length = 0;

	while (*s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}
