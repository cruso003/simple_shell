#include "shell.h"
Alias *alias_list = NULL;
/**
 * create_alias - Create a new alias structure
 * @name: the name of the alias structure
 * @value: the value to be used
 * Return: the new alias structure
 */
Alias *create_alias(const char *name, const char *value)
{
	Alias *new_alias = (Alias *)malloc(sizeof(Alias));

	if (new_alias == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	new_alias->name = strdup(name);
	if (new_alias->name == NULL)
	{
		perror("strdup");
		free(new_alias);
		return (NULL);
	}
	new_alias->value = strdup(value);
	if (new_alias->value == NULL)
	{
		perror("strdup");
		free(new_alias->name);
		free(new_alias);
		return (NULL);
	}
	new_alias->next = NULL;
	return (new_alias);
}

/**
 * free_alias_list - Free the alias list and associated memory
 */
void free_alias_list(void)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		Alias *next = current->next;

		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	alias_list = NULL;
}

/**
 * add_alias - Add a new alias to the alias list
 * @name: the name of the alias
 * @value: the value of the alias
 */
void add_alias(const char *name, const char *value)
{
	Alias *current = alias_list;
	Alias *prev = NULL;
	Alias *new_alias;

	while (current != NULL)
	{
		if (strcmp(name, current->name) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			return;
		}
		prev = current;
		current = current->next;
	}

	new_alias = create_alias(name, value);

	if (new_alias != NULL)
	{
		if (prev == NULL)
		{
			alias_list = new_alias;
		}
		else
		{
			prev->next = new_alias;
		}
	}
}

/**
 * print_aliases - Print aliases
 * @name: name of the alias
 */
void print_aliases(const char *name)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		if (name == NULL || (strcmp(name, current->name) == 0))
		{
			write(1, current->name, strlen(current->name));
			write(1, "='", 2);
			write(1, current->value, strlen(current->value));
			write(1, "'\n", 2);
		}
		current = current->next;
	}
}
/**
 * process_command - process command
 * @command: command to process
 */
void process_command(char *command)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		if (strcmp(command, current->name) == 0)
		{
			system(current->value);
			return;
		}
		current = current->next;
	}
	system(command);
}

/**
 * handle_alias - Handle the alias command
 * @tokens: the tokens to process
 */
void handle_alias(char **tokens)
{
	int i = 1;

	if (tokens[i] == NULL)
	{
		print_aliases(NULL);
	}
	else
	{
		while (tokens[i] != NULL)
		{
			if (strchr(tokens[i], '='))
			{
				char *name = strtok(tokens[i], "=");
				char *value = strtok(NULL, "");

				add_alias(name, value);
			}
			else
			{
				print_aliases(tokens[i]);
			}
			i++;
		}
	}
}
