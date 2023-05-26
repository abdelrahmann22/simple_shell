#include "shell.h"
/**
 * _getenv - gets an environment variable
 * @path_name: the name of the variable
 * Return: (Success) a pointer to the value of the variable
*/
char *_getenv(char *path_name)
{
	char **environ_cursor, *env_ptr, *name_ptr;

	environ_cursor = environ;
	while (*environ_cursor)
	{
		env_ptr = *environ_cursor;
		name_ptr = path_name;
		while (*env_ptr == *name_ptr)
		{
			if (*env_ptr == '=')
				break;
			env_ptr++;
			name_ptr++;
		}
		if ((*env_ptr == '=') && (*name_ptr == '\0'))
			return (env_ptr + 1);
		environ_cursor++;
	}
	return (NULL);
}
/**
 * signal_handler - handles the signal
 * @sig: the signal number
 * Return: void
*/

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		PRINT("\n");
		PRINT(PROMPT);
	}
}
/**
 * fill_an_array - fills an array with a given character
 * @array: the array to be filled
 * @elements: the number of elements to be filled
 * @length: the length of the array
 * Return: void
*/
void *fill_an_array(void *array, unsigned int elements, unsigned int length)
{
	char *p = array;
	unsigned int i = 0;

	while (i < length)
	{
		*p = elements;
		p++;
		i++;
	}
	return (array);
}
/**
 * array_rev - reverses an array
 * @array: the array to be reversed
 * @length: the length of the array
 * Return: void
*/
void array_rev(char *array, int length)
{
	int i;
	char tmp;

	for (i = 0; i < length / 2; i++)
	{
		tmp = array[i];
		array[i] = array[(length - 1) - i];
		array[(length - 1) - i] = tmp;
	}
}

/**
 * index_cmd - indexes the command
 * @data: the data struct
 * Return: void
*/
void index_cmd(shl_t *data)
{
	data->index += 1;
}
