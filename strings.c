#include "shell.h"

/**
 * beginwith - Checks if a string starts with a given prefix.
 * @str: The string to check.
 * @pref: The prefix to compare.
 * Return: 1 if str starts with pref, 0 otherwise.
 */
int beginwith(const char *str, const char *pref)
{
	size_t prefLength = strlen(pref);
	size_t strLength = strlen(str);

	if (prefLength > strLength)
		return (0);

	return (strncmp(str, pref, prefLength) == 0);
}

/**
 * strtrim - Trims leading and trailing spaces from a string.
 * @str: The string to be trimmed.
 * Return: A pointer to the trimmed character.
 */
char *strtrim(char *str)
{
	int len = strlen(str);
	int begin = 0;

	while (len > 0 && isspace((unsigned char)str[len - 1]))
	{
		len--;
	}
	str[len] = '\0';

	while (isspace((unsigned char)str[begin]))
		begin++;

	if (begin > 0)
		memmove(str, str + begin, len - begin + 1);

	return (str);
}
