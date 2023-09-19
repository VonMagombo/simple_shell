#include "shell.h"
/**
 * get_env - returns the string array copy of our _enviro
 * @data: structure to contain arguments. 
 * Return: Always 0
 */
char **get_env(pass_args_t *data)
{
	if (!data->_enviro || data->env_changed)
	{
		data->_enviro = get_strings(data->env);
		data->env_changed = 0;
	}
	return (data->_enviro);
}

/**
 * _unsetenv - removes environment variable
 * @data: structure containing potential arguments.
 * @var: string env var property
 * Return: 1 on delete, 0 otherwise
 *
 */
int _unsetenv(pass_args_t *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = begins_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			data->env_changed = del_node_index(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}

/**
 * _setenv - modifies an existing one
 * @data: structure containing potential arguments.
 * @var: string enviroment var property
 * @value: string env var value
 * Return: Always 0
 */
int _setenv(pass_args_t *data, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buffer = malloc(strlen(var) + strlen(value) + 2);
	if (!buffer)
		return (1);
	strcpy(buffer, var);
	strcat(buffer, "=");
	strcat(buffer, value);
	node = data->env;
	while (node)
	{
		ptr = begins_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	last_node_add(&(data->env), buffer, 0);
	free(buffer);
	data->env_changed = 1;
	return (0);
}
