#include "shell.h"

/**
 * replace_variables - replace environment variables in the input string
 * @input: input string
 * Return: replaced string
 */
char *replace_variables(const char *input);
char *replace_variables(const char *input)
{
	char *replaced = NULL;
	char *start = (char *)input;
	char *output = NULL;
	char *env_variable = NULL;
	char temp;
	size_t value_len, output_len, new_len, len;
	int last_exit_status = 0;
	char *new_output;
	char *env_value;

	while (*start)
	{
		if (start[0] == '$' && start[1] != '\0')
		{
			start++;
			if (start[0] == '?')
			{
				char str_last_exit_status[16];
				sprintf(str_last_exit_status, "%d", last_exit_status);
				env_variable = str_last_exit_status;
				start++;
			}
			else if (start[0] == '$')
			{
				char str_pid[16];
				sprintf(str_pid, "%d", getpid());
				env_variable = str_pid;
				start++;
			}
			else
			{
				env_variable = start;
				while (*start && (isalnum(*start) || *start == '_'))
				{
					start++;
				}
				if (start == env_variable)
				{
					free(replaced);
					continue;
				}

				temp = *start;
				*start = '\0';
				env_value = getenv(env_variable);
				*start = temp;

				if (env_value)
				{
					value_len = strlen(env_value);
					output_len = output ? strlen(output) : 0;
					new_len = output_len + value_len;

					new_output = (char *)malloc(new_len + 1);
					if (!new_output)
					{
						perror("malloc");
						free(replaced);
						return (NULL);
					}

					if (output_len > 0)
					{
						strcpy(new_output, output);
					}
					else
					{
						new_output[0] = '\0';
					}
					strcat(new_output, env_value);
					free(replaced);
					replaced = new_output;
				}
			}
		}

		if (!replaced)
		{
			len = output ? strlen(output) : 0;
			new_output = (char *)malloc(len + 2);
			if (!new_output)
			{
				perror("malloc");
				free(replaced);
				return (NULL);
			}
			if (len > 0)
			{
				strcpy(new_output, output);
			}
			else
			{
				new_output[0] = '\0';
			}
			new_output[len] = *start;
			new_output[len + 1] = '\0';
			free(output);
			output = new_output;
		}

		start++;
	}

	return (replaced ? replaced : (output ? output : strdup(input)));
}
