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
	/* Initialize buffer and line length*/
	char *buffer = NULL;
	size_t buffer_size = 0;
	size_t line_length = 0;
	int result;
	char *temp;

	if (lineptr == NULL || n == NULL)
	{
		return (-1);
	}

	while (1)
	{
		/*Ensure buffer has enough space*/
		if (line_length + 1 >= buffer_size)
		{
			buffer_size += 128;
			temp = (char *)realloc(buffer, buffer_size);

			if (temp == NULL)
			{
				free(buffer);
				*lineptr = NULL;
				return (-1);
			}
			buffer = temp;
		}

		/*Read a character from stdin*/
		result = read(STDIN_FILENO, buffer + line_length, 1);

		if (result < 0)
		{
			free(buffer);
			*lineptr = NULL;
			return (-1);
		}
		else if (result == 0)
		{
			/* EOF reached*/
			if (line_length == 0)
			{
				free(buffer);
				*lineptr = NULL;
				return (-1);
			}
			break;
		}
		else if (buffer[line_length] == '\n')
		{
			/* Newline encountered, terminate the string and return*/
			buffer[line_length] = '\0';
			break;
		}

		line_length++;
	}

	/* Allocate memory for the result line and copy data*/
	if (*lineptr == NULL)
	{
		*lineptr = (char *)malloc(line_length + 1);
		if (*lineptr == NULL)
		{
			free(buffer);
			return (-1);
		}
	}
	else if (*n < line_length + 1)
	{
		/**If provided buffer is too small, reallocate it*/
		char *temp = (char *)realloc(*lineptr, line_length + 1);

		if (temp == NULL)
		{
			free(buffer);
			*lineptr = NULL;
			return (-1);
		}
		*lineptr = temp;
	}

	/**Copy the data to the lineptr and free the temporary buffer*/
	strcpy(*lineptr, buffer);
	free(buffer);

	return (line_length);
}
