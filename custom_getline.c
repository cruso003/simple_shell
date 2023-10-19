#include "shell.h"

/**
 * custom_getline - Custom getline function with operator support
 * @lineptr: pointer to the line
 * @n: number of characters to get from the line
 * Return: bytes read from the line
 */
ssize_t custom_getline(char **lineptr, size_t *n);
ssize_t custom_getline(char **lineptr, size_t *n)
{
	ssize_t read = 0;
	int c;
	char *temp;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = (char *)malloc(sizeof(*n));
		if (*lineptr == NULL)
		{
			errno = ENOMEM;
			return (-1);
		}
	}
	while ((c = getchar()) != EOF)
	{
		if ((size_t)read >= *n)
		{
			*n += 128;
			temp = (char *)custom_realloc(*lineptr, *n);
			if (temp == NULL)
			{
				errno = ENOMEM;
				return (-1);
			}
			*lineptr = temp;
		}
		(*lineptr)[read] = (char)c;
		read++;

		if (c == '\n' || c == ';')
		{
			(*lineptr)[read] = '\0';
			return (read);
		}
		else if (c == '&' || c == '|')
		{
			int next_char = getchar();

			if (next_char == c)
			{
				(*lineptr)[read] = c;
				read++;
				(*lineptr)[read] = c;
				read++;
				(*lineptr)[read] = '\0';
				return (read);
			}
			else if (next_char != EOF)
			{
				ungetc(next_char, stdin);
			}
		}
	}
	if (read > 0)
	{
		(*lineptr)[read] = '\0';
		return (read);
	}
	return (0);
}
