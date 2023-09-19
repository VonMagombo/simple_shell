#include "shell.h"

/**
 * my_exit - exits the shell
 * @data: Structure containing potential arguments.
 *  Return: exits with a given exit status (0) if data.av[0] != "exit"
 */
int my_exit(pass_args_t *data)
{
	int exitchk;

	if (data->av[1])
	{
		exitchk = atoi_err(data->av[1]);
		if (exitchk == -1)
		{
			data->status = 2;
			print_err(data, "Number not valid ");
			puts_error(data->av[1]);
			putchar_error('\n');
			return (1);
		}
		data->error_exit = atoi_err(data->av[1]);
		return (-2);
	}
	data->error_exit = -1;
	return (-2);
}


/**
 * my_help - changes the current directory of the process
 * @data: structure containing potential arguments.
 * Return: Always 0.
 */
int my_help(pass_args_t *data)
{
	char **arg_array;

	arg_array = data->av;
	_puts("Call the help function.\n");
	if (0)
		_puts(*arg_array);
	return (0);
}

