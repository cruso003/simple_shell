#include "shell.h"
/**
 * execute_command - execute a command with arguments
 * @tokens: array of tokens representing the command and its arguments
 */
void execute_command(char **tokens);
void execute_command(char **tokens)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *command_name = tokens[0];
		char *envp[] = {"TERM=xterm", NULL};

		if (strchr(command_name, '/'))
		{
			if (execve(command_name, tokens, envp) == -1)
			{
				perror("Command execution failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			char *exec_path = find_full_path(command_name);

			if (exec_path == NULL)
			{
				fprintf(stderr, "Command not found: %s\n", command_name);
				exit(EXIT_FAILURE);
			}

			if (execve(exec_path, tokens, envp) == -1)
			{
				perror("Command execution failed");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
/**
 * tokenize_string - tokenize input string
 * @input: input string
 */
void tokenize_string(char *input);
void tokenize_string(char *input)
{
	char *token;
	char *delim = " \t\n;";
	char *input_cpy = _strdup(input);
	char **tokens = malloc(sizeof(char *) * MAX_TOKENS);
	int token_count = 0;
	int i;

	if (!input_cpy || !tokens)
	{
		perror("memory allocation failed");
		free(input_cpy);
		free(tokens);
		exit(EXIT_FAILURE);
	}
	token = custom_strtok(input_cpy, delim);
	while (token != NULL)
	{
		tokens[token_count] = _strdup(token);
		if (!tokens[token_count])
		{
			perror("memory allocation failed");
			exit(EXIT_FAILURE);
		}
		token_count++;
		token = custom_strtok(NULL, delim);
	}
	tokens[token_count] = NULL;

	if (token_count > 0)
	{
		if (!handle_builtin_commands(tokens))
		{
			execute_command(tokens);
		}
	}

	for (i = 0; i < token_count; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
	free(input_cpy);
}

/**
 * find_full_path - find full path of command line arguments
 * @command_name: command name of path
 * Return: full path
 */
char *find_full_path(const char *command_name)
{
	char full_path[1024];
	char *directory;
	const char *search_directories = getenv("PATH");
	char *path_copy = _strdup(search_directories);
	char *path_copy_copy;

	if (!path_copy)
	{
		perror("Path not specified");
		return (NULL);
	}

	path_copy_copy = _strdup(path_copy);

	directory = custom_strtok(path_copy_copy, ":");
	while (directory != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", directory, command_name);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			free(path_copy_copy);
			return (_strdup(full_path));
		}

		directory = custom_strtok(NULL, ":");
	}

	free(path_copy);
	free(path_copy_copy);
	return (NULL);
}

/**
 * evaluate_logical_expression - evaluate logical expression
 * @tokens: list of tokens
 * Return: logical expression
 */
int evaluate_logical_expression(char **tokens)
{
	int i;
	char *token;
	int left_hand_side_result;

	for (i = 0; i < MAX_TOKENS - 1; i++)
	{
		token = tokens[i];

		if (_strcmp(token, "&&") == 0)
		{

			left_hand_side_result = evaluate_logical_expression(tokens + i + 1);

			if (!left_hand_side_result)
			{
				return (0);
			}
		}
		else if (_strcmp(token, "||") == 0)
		{
			left_hand_side_result = evaluate_logical_expression(tokens + i + 1);

			if (left_hand_side_result)
			{
				return (1);
			}
		}
	}
	return (1);
}
