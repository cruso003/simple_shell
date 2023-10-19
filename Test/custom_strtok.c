#include "shell.h"

/**
 * custom_strtok - tokenize input string
 * @str: input string
 * @delim: delimiter string
 * Return: Next token or NULL when no more tokens are found
 */
char *custom_strtok(char *str, const char *delim)
{
	static char *buffer;
	char *token_start;

	if (str != NULL)
	{
		buffer = str;
	}
	if (buffer == NULL || *buffer == '\0')
	{
		return (NULL);
	}
	token_start = buffer;
	while (*buffer != '\0')
	{
		const char *d = delim;

		while (*d != '\0')
		{
			if (*buffer == *d)
			{
				*buffer = '\0';
				buffer++;
				if (token_start != buffer)
				{
					return (token_start);
				}
				else
				{
					token_start = buffer;
					break;
				}
			}
			d++;
		}
		buffer++;
	}
	return (token_start);
}

