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
	Alias *new_alias;
	Alias *current = alias_list;

	/*Check if value is an alias*/
	while (current != NULL)
	{
		if (strcmp(value, current->name) == 0)
		{
			/*f value is an alias, set new_alias to the value of the existing alias*/
			new_alias = create_alias(name, current->value);
			break;
		}
		current = current->next;
	}

	/*If value is not an alias, set new_alias normally*/
	if (current == NULL)
	{
		new_alias = create_alias(name, value);
	}

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
	Alias *current = alias_list;
	int found = 0;

	while (current != NULL)
	{
		if (name == NULL || (strcmp(name, current->name) == 0))
		{
			write(1, current->name, strlen(current->name));
			write(1, "='", 2);
			write(1, current->value, strlen(current->value));
			write(1, "'\n", 2);
			found = 1;
		}
		current = current->next;
	}

	if (!found)
	{
		printf("No alias found for '%s'\n", name);
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
			char *name = strtok(tokens[1], "=");
			char *value = strtok(NULL, "");

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
