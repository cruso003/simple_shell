#include "shell.h"

/**
 * handle_builtin_commands - Handle built-in commands
 * @tokens: Tokenized command and arguments
 * Return: 1 if a built-in command was handled, 0 otherwise
 */
int handle_builtin_commands(char **tokens);
int handle_builtin_commands(char **tokens)
{
	int i;
	char *endptr;

	if (handle_cd_command(tokens))
	{
		return (1);
	}
	else if (strcmp(tokens[0], "exit") == 0)
	{
		if (tokens[1] != NULL)
		{
			long status = strtol(tokens[1], &endptr, 10);

			if (*endptr != '\0')
			{
				fprintf(stderr, "Usage: exit status\n");
			}
			else
			{
				exit((int)status);
			}
		}
		return (1);
	}
	else if (strcmp(tokens[0], "echo") == 0)
	{
		for (i = 1; tokens[i] != NULL; i++)
		{
			write(1, tokens[i], strlen(tokens[i]));
			if (tokens[i + 1] != NULL)
			{
				write(1, " ", 1);
			}
		}
		write(1, "\n", 1);
		return (1);
	}
	else if (strcmp(tokens[0], "setenv") == 0)
	{
		if (tokens[1] == NULL || tokens[2] == NULL)
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			return (1);
		}
		else
		{
			if (setenv(tokens[1], tokens[2], 1) != 0)
			{
				perror("setenv");
				return (1);
			}
		}
		return (1);
	}
	else if (strcmp(tokens[0], "unsetenv") == 0)
	{
		if (tokens[1] == NULL)
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return (1);
		}
		else
		{
			if (unsetenv(tokens[1]) != 0)
			{
				perror("unsetenv");
				return (1);
			}
		}
		return (1);
	}
	else if (strcmp(tokens[0], "alias") == 0)
	{
		handle_alias(tokens);
		return (1);
	}
	else if (strcmp(tokens[0], "env") == 0)
	{
		return (handle_env_command());
	}

	return (0);
}

/**
 * handle_cd_command - Handle the cd and cd - commands
 * @tokens: Tokenized command and arguments
 * Return: 1 if a cd command was handled, 0 otherwise
 */
int handle_cd_command(char **tokens);
int handle_cd_command(char **tokens)
{
	int stdout_printed = 0;

	if (strcmp(tokens[0], "cd") == 0)
	{
		char *oldpwd = getcwd(NULL, 0);
		char *newdir = tokens[1] == NULL ||
							   strcmp(tokens[1], "~") == 0
						   ? getenv("HOME")
						   : tokens[1];

		if (newdir == NULL)
		{
			if (!stdout_printed)
			{
				write(1, oldpwd, strlen(oldpwd));
				stdout_printed = 0;
			}
			free(oldpwd);
			return (0);
		}

		if (strcmp(newdir, "-") == 0)
		{
			newdir = getenv("OLDPWD");
			if (newdir == NULL)
			{
				if (!stdout_printed)
				{
					printf("%s\n", oldpwd);
					stdout_printed = 1;
				}
				free(oldpwd);
				return (1);
			}
		}

		if (chdir(newdir) != 0)
		{
			fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", newdir);
			free(oldpwd);
			return (1);
		}

		if (strcmp(newdir, getenv("OLDPWD")) != 0)
		{
			setenv("OLDPWD", oldpwd, 1);
		}

		free(oldpwd);
		return (1);
	}

	return (0);
}

/**
 * handle_env_command - Handle the env command
 * Return: 1 if the command was handled, 0 otherwise
 */
int handle_env_command(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(1, environ[i], strlen(environ[i]));
		write(1, "\n", 1);
	}

	return (1);
}