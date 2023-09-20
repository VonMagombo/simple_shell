#include "shell.h"
/**
 * my_env - prints the current environment
 * @data: structure with potential arguments.
 * Return: Always 0
 */
int my_env(pass_args_t *data)
{
	print_str(data->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @data: structure with potential arguments.
 * @name: argument
 * Return: the value
 */
char *_getenv(pass_args_t *data, const char *name)
{
	list_t *node = data->env;
	char *p;

	while (node)
	{
		p = begins_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - modifies an existing one
 * @data: structure with potential arguments.
 * Return: Always 0
 */
int my_setenv(pass_args_t *data)
{
	if (data->ac != 3)
	{
		puts_error("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(data, data->av[1], data->av[2]))
		return (0);
	return (1);
}

/**
 * Custom_unsetenv - removes an environment variable
 * @data: structure with potential argumemts
 *  Return: Always 0
 */
int Custom_unsetenv(pass_args_t *data)
{
	int i;

	if (data->ac == 1)
	{
		puts_error("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= data->ac; i++)
		_unsetenv(data, data->av[i]);

	return (0);
}

/**
 * env_list_populater - populates environment linked list
 * @data: structures with potential arguments.
 * Return: Always 0
 */
int env_list_populater(pass_args_t *data)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		last_node_add(&node, environ[i], 0);
	data->env = node;
	return (0);
}

