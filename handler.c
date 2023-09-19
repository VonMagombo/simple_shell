#include "shell.h"
/**
 * seek_builtin - finds a builtin command
 * @data: the parameter & return data struct
 * Return: -1 if builtin not found, 0 if successful
 */
int seek_builtin(pass_args_t *data)
{
	int i, builtin_return = -1;
	builtin_tb builtincmd[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"setenv", my_setenv},
		{"unsetenv", Custom_unsetenv},
		{"cd", Custom_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtincmd[i].type; i++)
		if (strcmp(data->av[0], builtincmd[i].type) == 0)
		{
			data->line_count++;
			builtin_return = builtincmd[i].func(data);
			break;
		}
	return (builtin_return);
}

/**
 * _find - finds a command in PATH
 * @data: the parameter & return data struct
 * Return: void
 */
void _find(pass_args_t *data)
{
	char *path = NULL;
	int i, k;

	data->path = data->av[0];
	if (data->flag_Line_Count == 1)
	{
		data->line_count++;
		data->flag_Line_Count = 0;
	}
	for (i = 0, k = 0; data->arg_c[i]; i++)
		if (!is_delim(data->arg_c[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = seek_path(data, _getenv(data, "PATH="), data->av[0]);
	if (path)
	{
		data->path = path;
		_fork(data);
	}
	else
	{
		if ((_interact(data) || _getenv(data, "PATH=")
			|| data->av[0][0] == '/') && is_cmd(data, data->av[0]))
			_fork(data);
		else if (*(data->arg_c) != '\n')
		{
			data->status = 127;
			print_err(data, "not found\n");
		}
	}
}
