#include "shell.h"

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
	new_alias->name = _strdup(name);
	if (new_alias->name == NULL)
	{
		perror("strdup");
		free(new_alias);
		return (NULL);
	}
	new_alias->value = _strdup(value);
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
	Alias *alias_list = NULL;
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
	Alias *alias_list = NULL;
	Alias *new_alias = create_alias(name, value);

	if (new_alias != NULL)
	{
		new_alias->next = alias_list;
		alias_list = new_alias;
	}
}

/**
 * print_aliases - Print aliases
 * @name: name of the alias
 */
void print_aliases(const char *name)
{
	Alias *alias_list = NULL;
	Alias *current = alias_list;

	while (current != NULL)
	{
		if (name == NULL || (_strcmp(name, current->name) == 0))
		{
			printf("alias %s='%s'\n", current->name, current->value);
		}
		current = current->next;
	}
}

/**
 * handle_alias - Handle the alias command
 * @tokens: the tokens to process
 */
void handle_alias(char **tokens)
{
	if (tokens[1] == NULL)
	{
		print_aliases(NULL);
	}
	else
	{
		if (strchr(tokens[1], '='))
		{
			char *name = custom_strtok(tokens[1], "=");
			char *value = custom_strtok(NULL, "");

			add_alias(name, value);
		}
		else
		{
			int i;

			for (i = 1; tokens[i] != NULL; i++)
			{
				print_aliases(tokens[i]);
			}
		}
	}
}
