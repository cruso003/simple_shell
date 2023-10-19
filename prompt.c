#include "shell.h"
/**
 * get_user_input - get the user input from the line
 * @lineptr: the line pointer to get the user input from
 * the line
 * @n: the number of characters to get from the line
 * Return: the number of characters received
 */
ssize_t get_user_input(char **lineptr, size_t *n)
{
	char *prompt = "$ ";
	size_t read;

	if (write(1, prompt, strlen(prompt)) == -1)
	{
		perror("write error");
		return (-1);
	}
	read = getline(lineptr, n);
	if (!read)
	{
		return (-1);
	}
	return (read);
}
