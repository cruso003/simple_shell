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
	int command_not_found = 0;
	pid_t wait_result;

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
				exit(2);
			}
		}
		else
		{
			char *exec_path = find_full_path(command_name);

			if (exec_path == NULL)
			{

				exit(2);
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
		if (command_not_found)
		{
			exit(2); /* Set exit status to indicate command not found*/
		}
		wait_result = (waitpid(child_pid, &status, 0));
		if (wait_result == -1)
		{
			exit(2);
		}

		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);

			if (exit_status == 2)
			{
				command_not_found = 1;
			}
		}
	}
}

/**
 * tokenize_string - tokenize input string
 * @input: input string
 */
void tokenize_string(char *input);
void tokenize_string(char *input)
{
	char *trimmed_input = input;
	char *token;
	char *delim = " \t\n;";
	char **tokens = malloc(sizeof(char *) * MAX_TOKENS);
	int token_count = 0;
	int i;
	char *end;

	while (*trimmed_input == ' ' || *trimmed_input == '\t')
	{
		trimmed_input++;
	}
	end = trimmed_input + strlen(trimmed_input) - 1;
	while (end > trimmed_input && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}

	if (!tokens)
	{
		perror("memory allocation failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(trimmed_input, delim);
	while (token != NULL)
	{
		tokens[token_count] = strdup(token);
		if (!tokens[token_count])
		{
			perror("memory allocation failed");
			exit(EXIT_FAILURE);
		}
		token_count++;
		token = strtok(NULL, delim);
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
	char *path_copy = strdup(search_directories);
	char *path_copy_copy;

	if (search_directories == NULL || search_directories[0] == '\0')
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command_name);
		return (NULL);
	}
	if (!path_copy)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command_name);
		return (NULL);
	}

	path_copy_copy = strdup(path_copy);

	directory = strtok(path_copy_copy, ":");
	while (directory != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", directory, command_name);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			free(path_copy_copy);
			return (strdup(full_path));
		}

		directory = strtok(NULL, ":");
	}

	free(path_copy);
	free(path_copy_copy);
	return (NULL);
}
