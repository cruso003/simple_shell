#include "shell.h"

/**
 * _strcpy - copies a string from src to dest.
 * @dest: pointer to the destination buffer
 * @src: pointer to the source string
 *
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
