#include "shell.h"
/**
 * main - main function
 * @argc: number of arguments
 * @argv: command line arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *filename = argv[1];
	char *input = NULL;
	size_t len = 0;
	FILE *file;
	char *replaced_input;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	file = fopen(filename, "r");
	if (file == NULL)
	{
		perror("fopen");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		ssize_t read = get_user_input(&input, &len);

		if (read == -1)
		{
			break;
		}
		if (input[0] == '#')
		{
			continue;
		}
		replaced_input = replace_variables(input);
		tokenize_string(replaced_input);

		free(replaced_input);
	}

	fclose(file);
	free(input);

	return (EXIT_SUCCESS);
}