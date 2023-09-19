#include "shell.h"

/**
 * clear_data - clears pass_args_t struct
 * @data: struct address
 */
void clear_data(pass_args_t *data)
{
	data->arg_c = NULL;
	data->av = NULL;
	data->path = NULL;
	data->ac = 0;
}

/**
 * set_data - initialises pass_args_t struct
 * @data: struct address
 * @av: argument vector
 */
void set_data(pass_args_t *data, char **av)
{
	int i = 0;

	data->fname = av[0];
	if (data->arg_c)
	{
		data->av = _strtok(data->arg_c, " \t");
		if (!data->av)
		{

			data->av = malloc(sizeof(char *) * 2);
			if (data->av)
			{
				data->av[0] = _strdup(data->arg_c);
				data->av[1] = NULL;
			}
		}
		for (i = 0; data->av && data->av[i]; i++)
			;
		data->ac = i;

		replace_alias(data);
		replace_var(data);
	}
}

/**
 * free_data - frees pass_args_t struct fields
 * @data: address of struct
 * @_free: frees all fields
 */
void free_data(pass_args_t *data, int _free)
{
	free_str(data->av);
	data->av = NULL;
	data->path = NULL;
	if (_free)
	{
		if (!data->cmd_buffer)
			free(data->arg_c);
		if (data->env)
			free_list(&(data->env));
		if (data->node_alias)
			free_list(&(data->node_alias));
		free_str(data->_enviro);
			data->_enviro = NULL;
		free_up((void **)data->cmd_buffer);
		if (data->readfhand > 2)
			close(data->readfhand);
		_putchar(BUFFER_FLUSH);
	}
}
