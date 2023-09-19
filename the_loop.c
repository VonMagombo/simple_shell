#include "shell.h"

/**
 * buddie_loop - shell loop
 * @data: parameter data struct
 * @av: argument vector 
 * Return: 0 on success otherwise, 1 
 */
int buddie_loop(pass_args_t *data, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_data(data);
		if (_interact(data))
			_puts("buddies$ ");
		putchar_error(BUFFER_FLUSH);
		r = getInput(data);
		if (r != -1)
		{
			set_data(data, av);
			builtin_ret = seek_builtin(data);
			if (builtin_ret == -1)
				_find(data);
		}
		else if (_interact(data))
			_putchar('\n');
		free_data(data, 0);
	}
	free_data(data, 1);
	if (!_interact(data) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->error_exit == -1)
			exit(data->status);
		exit(data->error_exit);
	}
	return (builtin_ret);
}

/**
 * _fork - forks an exec thread to run cmd
 * @data: the parameter data struct
 * Return: void
 */
void _fork(pass_args_t *data)
{
	pid_t _child_pid;

	_child_pid = fork();
	if (_child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (_child_pid == 0)
	{
		if (execve(data->path, data->av, get_env(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(200);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 200)
				print_err(data, "Permission Denied!!\n");
		}
	}
}

