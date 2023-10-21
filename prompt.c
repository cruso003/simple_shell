#include "shell.h"
/**
 * get_user_input - get the user input from the line
 * @lineptr: the line pointer to get the user input from
 * the line
 * @n: the number of characters to get from the line
 * @stream: the stream to get the user input from
 * Return: the number of characters received
 */
ssize_t get_user_input(char **lineptr, size_t *n, FILE *stream)
{
	int is_terminal = isatty(fileno(stream));
	ssize_t read;

	if (is_terminal)
	{
		char *prompt = "$ ";
		write(1, prompt, strlen(prompt));
	}

	read = getline(lineptr, n, stream);

	if (!is_terminal && read == -1)
	{
		return (-1);
	}

	if (is_terminal && read > 0 && (*lineptr)[read - 1] == '\n')
	{
		(*lineptr)[read - 1] = '\0';
		read--;
	}
	return (read);
}
