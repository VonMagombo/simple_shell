#include "shell.h"

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @data: parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(pass_args_t *data)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_prefix(data->node_alias, data->av[0], '=');
		if (!node)
			return (0);
		free(data->av[0]);
		ptr = strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		data->av[0] = ptr;
	}
	return (1);
}

/**
 * chain_deli - checks if  the current char in  the buffer is a chain delimeter
 * @data: parameter struct
 * @buf: char buffer
 * @ptr: address of current position in buffer
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain_deli(pass_args_t *data, char *buf, size_t *ptr)
{
	size_t x = *ptr;

	if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		data->buffer_type = _OR;
	}
	else if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		data->buffer_type = _AND;
	}
	else if (buf[x] == ';') 
	{
		buf[x] = 0; 
		data->buffer_type = _CHAIN;
	}
	else
		return (0);
	*ptr = x;
	return (1);
}

/**
 * replace_str - replaces string
 * @former: address of former string
 * @latest: latest string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_str(char **former, char *latest)
{
	free(*former);
	*former = latest;
	return (1);
}

/**
 * replace_var - replaces vars in the tokenized string
 * @data: parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_var(pass_args_t *data)
{
	int i = 0;
	list_t *node;

	for (i = 0; data->av[i]; i++)
	{
		if (data->av[i][0] != '$' || !data->av[i][1])
			continue;

		if (!strcmp(data->av[i], "$?"))
		{
			replace_str(&(data->av[i]),
				_strdup(itoa_rep(data->status, 10, 0)));
			continue;
		}
		if (!strcmp(data->av[i], "$$"))
		{
			replace_str(&(data->av[i]),
				_strdup(itoa_rep(getpid(), 10, 0)));
			continue;
		}
		node = node_prefix(data->env, &data->av[i][1], '=');
		if (node)
		{
			replace_str(&(data->av[i]),
				_strdup(strchr(node->str, '=') + 1));
			continue;
		}
		replace_str(&data->av[i], _strdup(""));

	}
	return (0);
}
