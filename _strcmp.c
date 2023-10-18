#include "shell.h"
/**
 * _strcmp - a function that compares two strings.
 * @s1: string 1 being compared
 * @s2: string 2 being compared
 *
 * Return: 0 if equal, negative if s1 < s2, positive if s1 >  s2.
 */
int _strcmp(const char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
