#include "shell.h"
/**
 * _memcpy - copies memory area
 * @dest: destination memory area
 * @src: memory area to copy from
 * @n: number of bytes to copy
 *
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}
/**
 * custom_realloc - allocate memory for a new object and return a pointer to it
 * @ptr: pointer to the new object
 * @size: size of the new object
 * Return: pointer to the new object
 */
void *custom_realloc(void *ptr, size_t size)
{
	void *newptr;

	if (size == 0)
	{
		if (ptr)
		{
			free(ptr);
		}
		return (NULL);
	}
	newptr = malloc(size);

	if (!newptr)
	{
		errno = ENOMEM;
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		_memcpy(newptr, ptr, size);
	}
	free(ptr);
	return (newptr);
}
