#include "shell.h"

/**
 * custom_getline - read one line from the prompt.
 * @data: struct for the program's data
 *
 * Return: reading counting bytes.
 */
int custom_getline(program_info *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char arr_operators[10] = {'\0'};
	static char *arr_commands[10] = {NULL};
	ssize_t bytes_read, i = 0;

	if (!arr_commands[0] || (arr_operators[0] == '&' && errno != 0) ||
		(arr_operators[0] == '|' && errno == 0))
	{
		for (i = 0; arr_commands[i]; i++)
		{
			free(arr_commands[i]);
			arr_commands[i] = NULL;
		}
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do
		{
			arr_commands[i] = _strdup(custom_strtok(i ? NULL : buff, "\n;"));
			i = logical_operator(arr_commands, i, arr_operators);
		} while (arr_commands[i++]);
	}
	data->input_line = arr_commands[0];
	for (i = 0; arr_commands[i]; i++)
	{
		arr_commands[i] = arr_commands[i + 1];
		arr_operators[i] = arr_operators[i + 1];
	}

	return (_strlen(data->input_line));
}

/**
 * check_logic_ops - checks and split for && and || operators
 * @arr_commands: array of the commands.
 * @l: index in the array_commands to be checked
 * @array_operators: array of the logical operators for each previous command
 *
 * Return: index of the last command in the array_commands.
 */
int logical_operator(char *arr_commands[], int l, char arr_operators[])
{
	char *temp = NULL;
	int c;

	for (c = 0; arr_commands[l] != NULL && arr_commands[l][c]; c++)
	{
		if (arr_commands[l][c] == '&' && arr_commands[l][c + 1] == '&')
		{
			temp = arr_commands[l];
			arr_commands[l][c] = '\0';
			arr_commands[l] = _strdup(arr_commands[l]);
			arr_commands[l + 1] = _strdup(temp + c + 2);
			l++;
			arr_operators[l] = '&';
			free(temp);
			c = 0;
		}
		if (arr_commands[l][c] == '|' && arr_commands[l][c + 1] == '|')
		{
			temp = arr_commands[l];
			arr_commands[l][c] = '\0';
			arr_commands[l] = _strdup(arr_commands[l]);
			arr_commands[l + 1] = _strdup(temp + c + 2);
			l++;
			arr_operators[l] = '|';
			free(temp);
			c = 0;
		}
	}
	return (l);
}