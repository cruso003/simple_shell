#include "shell.h"

/**
 * main - main function
 * @argc: number of arguments
 * @argv: command line arguments
 * Return: 0 on success
 */
int main(int argc, char **argv);
int main(int argc, char **argv)
{
	char *filename = NULL;
	char *input = NULL;
	size_t len = 0;
	FILE *file;
	char *replaced_input;

	(void)argc;
	(void)argv;

	if (argc == 2)
	{
		filename = argv[1];
		file = fopen(filename, "r");
		if (file == NULL)
		{
			fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], filename);
			return (127);
		}
	}

	else if (argc > 2)
	{
		fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	while (1)
	{
		ssize_t read = get_user_input(&input, &len, file ? file : stdin);

		if (read == -1)
		{
			break;
		}
		if (input[0] == '#' || (input[0] == ' ' && input[1] == '#'))
		{
			continue;
		}
		replaced_input = replace_variables(input);
		tokenize_string(replaced_input);

		free(replaced_input);
	}

	if (filename)
	{
		fclose(file);
	}
	free(input);

	return (EXIT_SUCCESS);
}