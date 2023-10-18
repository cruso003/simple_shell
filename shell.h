#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stddef.h>
#include <ctype.h>
#include <limits.h>

#define MAX_TOKENS 128

/**
 * struct Alias - Structure to represent an alias
 * @name: alias name
 * @value: alias value
 * @next: pointer to the next alias
 */
typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} Alias;

/** Function to read user input*/
ssize_t get_user_input(char **lineptr, size_t *n);

/** Function to tokenize an input string*/
void tokenize_string(char *input);

/** Function to replace variables in a string*/
char *replace_variables(const char *input);

/** Function to handle built-in commands*/
int handle_builtin_commands(char **tokens);

/** Function to execute logical commands (e.g., && and ||)*/
int evaluate_logical_expression(char **tokens);

/** Custom getline function*/
ssize_t custom_getline(char **lineptr, size_t *n);

/** Custom realloc function for memory allocation*/
void *custom_realloc(void *ptr, size_t size);

/** Custom function for strlen*/
int _strlen(char *s);

/** Custom function for strcpy*/
char *_strcpy(char *dest, char *src);

/** Function to copy memory from src to dest*/
char *_memcpy(char *dest, char *src, unsigned int n);

/** Custom strtok function*/
char *custom_strtok(char *str, const char *delim);

/** Function to create an alias*/
Alias *create_alias(const char *name, const char *value);

/** Function to free the alias*/
void free_alias_list(void);

/** Function to add an alias*/
void add_alias(const char *name, const char *value);

/** Function to print aliases (for debugging)*/
void print_aliases(const char *name);

/** Function to handle 'the alias' command*/
void handle_alias(char **tokens);

/** Function to find command full path*/
char *find_full_path(const char *command_name);

/** Function to execute our tokens*/
void execute_command(char **tokens);

/** Function to handle cd and cd -*/
int handle_cd_command(char **tokens);

/** Function to handle environment printing*/
int handle_env_command(void);

/** Function to handle the separator ";"*/
void tokenize_and_execute_commands(char *input);

/** Function to trim the input*/
char *trim(char *str);

/** Custom function for string comparing*/
int _strcmp(char *s1, char *s2);

/** Custom function for string duplicating*/
char *_strdup(char *str);
#endif
