#include "shell.h"
/**
 * is_path_format - checks if the path is in the format of PATH
 * @data: the data struct
 * Return: 0 on success, -1 on failure
 */
int is_path_format(shl_t *data)
{
	if (_strchar(data->args[0], '/') != 0)
	{
		data->cmd = _strdup(data->args[0]);
		return (SUCCESS);
	}
	return (FAIL);
}
#define DELIMITER ":"

/**
 * is_short_format - checks if the path is in the format of PATH
 * @data: the data struct
 * Return: 0 on success, -1 on failure 
 */
void is_short_format(shl_t *data)
{
	char *path, *token, *_path;
	struct stat st;
	int exist_flag = 0;

	path = _getenv("PATH");
	_path = _strdup(path);
	token = strtok(_path, DELIMITER);
	while (token != NULL)
	{
		data->cmd = _strcat(token, data->args[0]);
		if (stat(data->cmd, &st) == 0)
		{
			exist_flag += 1;
			break;
		}
		free(data->cmd);
		token = strtok(NULL, DELIMITER);
	}
	if (exist_flag == 0)
	{
		data->cmd = _strdup(data->args[0]);
	}
	free(_path);
}
#undef DELIMITER

/**
 * is_builtin - checks if the command is a builtin
 * @data: the data struct
 * Return: 0 on success, -1 on failure 
 */
int is_builtin(sh_t *data)
{
	builtin_t bit[] = {
		{"exit", abort_prog},
		{"help", display_help},
		{"cd", change_dir},
		{NULL, NULL}
	};
	int i = 0;

	while (bit[i].cmd != NULL)
	{
		if (_strcmp(data->args[0], bit[i]->cmd) == 0)
		{
			return (SUCCESS);
		}
		i++;
	}
	return (NEUTRAL);
}
