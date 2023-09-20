#include "shell.h"

/**
 * reset_alias - sets the alias to string
 * @data: parameter struct
 * @str: string alias
 * Return: always 0 on success otherwise, 1
 */
int reset_alias(pass_args_t *data, char *str)
{
	char *x, c;
	int val;

	x = strchr(str, '=');
	if (!x)
		return (1);
	c = *x;
	*x = 0;
	val = del_node_index(&(data->node_alias),
		node_index_getter(data->node_alias, node_prefix(data->node_alias, str, -1)));
	*x = c;
	return (val);
}

/**
 * alias_setter - sets alias to string
 * @data: parameter struct
 * @str: string alias
 * Return: Always 0 on success, 1 on error
 */
int alias_setter(pass_args_t *data, char *str)
{
	char *ptr;

	ptr = strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (reset_alias(data, str));

	reset_alias(data, str);
	return (last_node_add(&(data->node_alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: alias node
 * Return: 0 on success otherwise, 1
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = strchr(node->str, '=');
		for (a = node->str; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * Custom_cd - changes the current directory
 * @data: structure containing potential arguments.
 * Return: Always 0
 */
int Custom_cd(pass_args_t *data)
{
	char *s, *dir, buf[1024];
	int chdir_ret;

	s = getcwd(buf, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure error message here<<\n");
	if (!data->av[1])
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (strcmp(data->av[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data->av[1]);
	if (chdir_ret == -1)
	{
		print_err(data, "can't cd to ");
		puts_error(data->av[1]), putchar_error('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * my_alias - mimics the alias function
 * @data: structure containing some arguments.
 *  Return: Always 0
 */
int my_alias(pass_args_t *data)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (data->ac == 1)
	{
		node = data->node_alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->av[i]; i++)
	{
		ptr = strchr(data->av[i], '=');
		if (ptr)
			alias_setter(data, data->av[i]);
		else
			print_alias(node_prefix(data->node_alias, data->av[i], '='));
	}

	return (0);
}
