#include "shell.h"

static char input_buffer[BUFFER_SIZE];
static size_t buffer_position;
static size_t buffer_size;

/**
 * custom_getline - Custom getline function with operator support
 * @lineptr: pointer to the line
 * @n: number of characters to get from the line
 * Return: bytes read from the line
 */
ssize_t custom_getline(char **lineptr, size_t *n);
ssize_t custom_getline(char **lineptr, size_t *n)
{
	size_t line_length = 0;
	char *line = NULL;
	int c;

	if (lineptr == NULL || n == NULL)
	{
		return (-1);
	}

	if (buffer_position >= buffer_size)
	{
		ssize_t bytes_read = read(STDIN_FILENO, input_buffer, BUFFER_SIZE);

		if (bytes_read <= 0)
		{
			return (bytes_read);
		}
		buffer_position = 0;
		buffer_size = (size_t)bytes_read;
	}

	while (buffer_position < buffer_size)
	{
		c = input_buffer[buffer_position++];
		if (c == '\n' || c == '\0')
		{
			if (line_length > 0)
			{
				line[line_length] = '\0';
				*lineptr = line;
				*n = line_length;
				return (line_length);
			}
		}
		else
		{
			if (line_length == 0)
			{
				line = (char *)malloc(2 * sizeof(char));
				if (line == NULL)
				{
					return (-1);
				}
			}
			else
			{
				char *temp = (char *)realloc(line, (line_length + 2) * sizeof(char));

				if (temp == NULL)
				{
					free(line);
					return (-1);
				}
				line = temp;
			}
			line[line_length++] = (char)c;
		}
	}

	return (-1);
}
