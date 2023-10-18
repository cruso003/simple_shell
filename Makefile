# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

# Executable name
EXECUTABLE = hsh

# Source files
SRCS = _strcmp.c _strcpy.c _strdup.c _strlen.c alias.c builtin.c custom_getline.c custom_realloc.c custom_strtok.c prompt.c replace_variables.c shell.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build the executable
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean build artifacts
clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: clean
