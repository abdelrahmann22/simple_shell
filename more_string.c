#include "shell.h"
/**
 * _strcpy - copies a string
 * @dest: the destination string
 * @src: the source string
 * Return: (Success) a pointer to the destination string
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = src[i];
	return (dest);
}

/**
 * _isalpha - checks if a character is alphabetic
 * @c: the character to be checked
 * Return: (Success) 1 if c is a letter, 0 otherwise
*/
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') ||
	    (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
