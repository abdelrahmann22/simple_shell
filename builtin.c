#include "shell.h"

#define SETOWD(V) (V = _strdup(_getenv("OLDPWD")))

/**
 * change_dir - changes dir
 * @data: the data struct
 * Return: 0 on success, -1 on failure
 */

int change_dir(shl_t *data)
{
	char *home;

	home = _getenv("HOME");
	if (data->args[1] == NULL)
	{
		SETOWD(data->oldpwd);
		if (chdir(home) < 0)
			return (FAIL);
		return (SUCCESS);
	}
	if (_strcmp(data->args[1], "-" == 0))
	{
		if (data->oldpwd == NULL)
		{
			SETOWD(data->oldpwd);
			if (chdir(home) < 0)
				return (FAIL);
		}
		else
		{
			SETOWD(data->oldpwd);
			if (chdir(data->oldpwd) < 0)
				return (FAIL);
		}
	}
	else
	{
		SETOWD(data->oldpwd);
		if (chdir(data->args[1]) < 0)
			return (FAIL);
	}
	return (SUCCESS);
}
#undef GETCWD
/**
 * display_help - displays help
 * @data: the data struct
 * Return: 0 on success, -1 on failure
*/

int abort_prog(shl_t *data __attribute__((unused)))
{
	int code, i = 0;

	if (data->args[1] == NULL)
	{
		free_data(data);
		exit(errno);
	}
	while (data->args[1][i])
	{
		if (_isalpha(data->args[1][i++]) < 0)
		{
			data->error_msg = _strdup("exit: Illegal number: ");
			return (FAIL);
		}
	}
	code = _atoi(data->args[1]);
	free_data(data);
	exit(code);
}
int display_help(shl_t *data)
{
	int fd, fw, rd = 1;
	char c;

	fd = open(data->args[1], O_RDONLY);
	if (fd < 0)
	{
		data->error_msg = _strdup("help: no help topics match\n");
		return (FAIL);
	}
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		fw = write(STDOUT_FILENO, &c, 1);
		if (fw < 0)
		{
			data->error_msg = _strdup("help: no help topics match\n");
			return (FAIL);
		}
	}
	PRINT("\n");
	return (SUCCESS);
}
/**
 * handle_builtin - handles builtin
 * @data: the data struct
 * Return: 0 on success, -1 on failure
 */
int handle_builtin(shl_t *data)
{
	builtin_t builtins[] = {
		{"cd", change_dir},
		{"exit", abort_prog},
		{"help", display_help},
		{NULL, NULL}
	};
	int i = 0;

	while ((builtins + i)->cmd)
	{
		if (_strcmp(data->args[0], (builtins + i)->cmd) == 0)
			return ((builtins + i)->f(data));
		i++;
	}
	return (FAIL);
}
