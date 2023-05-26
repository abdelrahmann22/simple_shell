#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * Return: (Success) a pointer to the destination string
*/

char *_strcat(char *dest, char *src)
{
	int len1, len2, i = 0, j = 0;
	char *result;

	len1 = _strlen(dest);
	len2 = _strlen(src);
	result = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!result)
		return (NULL);
	*result = '\0';
	while (dest[i] != '\0')
	{
		result[i] = dest[i];
		i++;
	}
	result[i++] = '/';
	j = 0;
	while (src[j] != '\0')
	{
		result[i] = src[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}
/**
 * _strlen - returns the length of a string
 * @str: the string to be checked
 * Return: (Success) the length of the string
*/
int _strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}
/**
 * _strcmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 * Return: (Success) the difference between the strings
*/
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/**
 * _strchr- locates a character in a string
 * @str: the string to be duplicated
 * Return: (Success) a pointer to the duplicated char
*/
char *_strchr(char *str, char c)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}
/**
 * _strdup - duplicates a string
 * @str: the string to be duplicated
 * Return: (Success) a pointer to the duplicated string
*/
char *_strdup(char *str)
{
	int len, i = 0;
	char *result;

	len = _strlen(str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

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
