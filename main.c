#include "shell.h"

/**
 * main - the main function
 * Return: 0 on success, -1 on failure
*/

int main(void)
{
	shl_t data;
	int pl;

	_memset((void *)&data, 0, sizeof(data));
	signal(SIGINT, singal_hander);
	while (1)
	{
		index_cmd(&data);
		if (read_line(&data) < 0)
		{
			if (isatty(STDIN_FILENO))
				PRINT("\n");
			break;
		}
		if (split_line(&data) < 0)
		{
			free_data(&data);
			continue;
		}
		pl = parse_line(&data);
		if (pl == 0)
		{
			free_data(&data);
			continue;
		}
		if (pl < 0)
		{
			print_error(&data);
			continue;
		}
		if (process_cmd(&data) < 0)
		{
			print_error(&data);
			break;
		}
		free_data(&data);
	}
	free_data(&data);
	exit(EXIT_SUCCESS);
}

/**
 * read_line - reads the line
 * @data: the data struct
 * Return: 0 on success, -1 on failure
*/

int read_line(shl_t *data)
{
	char *csr_ptr, *end_ptr, c;
	size_t size = BUFSIZE, read_st, length, new_size;

	data->line = malloc(sizeof(char) * size);
	if (data->line == NULL)
		return (FAIL);
	if (isatty(STDIN_FILENO))
		PRINT(PROMPT);
	for (csr_ptr = data->line, end_ptr = end->line + size;;)
	{
		read_st = read(STDIN_FILENO, &c, 1);
		if (read_st == 0)
			return (FAIL);
		*csr_ptr++ = c;
		if (c == '\n')
		{
			*csr_ptr = '\0';
			return (SUCCESS);
		}
		if (csr_ptr + 2 >= end_ptr)
		{
			new_size = size * 2;
			length = csr_ptr - data->line;
			data->line = _realloc(data->line, size, new_size * sizeof(char));
			if (data->line == NULL)
				return (FAIL);
			size = new_size;
			csr_ptr = data->line + length;
			end_ptr = data->line + size;
		}
	}
}

#define DELIMITER " \t\n\a\r\v"

/**
 * split_line - splits the line
 * @data: the data struct
 * Return: 0 on success, -1 on failure
*/

int split_line(shl_t *data)
{
	char *token, **tokens;
	size_t size = BUFSIZE, index = 0;
	int i;

	tokens = malloc(sizeof(char *) * size);
	if (tokens == NULL)
		return (FAIL);
	token = strtok(data->line, DELIMITER);
	while (token != NULL)
	{
		tokens[index] = token;
		index++;
		if (index >= size)
		{
			size += BUFSIZE;
			tokens = _realloc(tokens, size * sizeof(char *), size * sizeof(char *));
			if (tokens == NULL)
				return (FAIL);
		}
		token = strtok(NULL, DELIMITER);
	}
	tokens[index] = NULL;
	data->args = tokens;
	for (i = 0; data->args[i] != NULL; i++)
		;
	data->index = i;
	return (SUCCESS);
}
#undef DELIMITER
#define DELIMITER ":"

/**
 * parse_line - parses the line
 * @data: the data struct
 * Return: 0 on success, -1 on failure
*/

int parse_line(sh_t *data)
{
	if (is_path_format(data) > 0)
		return (SUCCESS);
	if (is_builtin(data) > 0)
	{
		if (handle_builtin(data) < 0)
			return (FAIL);
		return (NEUTRAL);
	}
	is_short_format(data);
	return (SUCCESS);
}

#undef DELIMITER

/**
 * process_cmd - process the command
 * @data: the data struct
 * Return: 0 on success, -1 on failure
*/

int process_cmd(shl_t *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(data->args[0], data->args, environ) == -1)
		{
			print_error(data);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		print_error(data);
		return (FAIL);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (SUCCESS);
}
