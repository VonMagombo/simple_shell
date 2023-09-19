#include "shell.h"

/**
 * dup_char - duplicates characters
 * @path_str: the PATH string
 * @begin: start index
 * @end: stop index
 * Return: pointer to new buffer
 */
char *dup_char(char *path_str, int begin, int end)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = begin; i < end; i++)
		if (path_str[i] != ':')
			buf[k++] = path_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * is_cmd - determines if a file is an executable command
 * @data: data struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(pass_args_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode)
	{
		return (1);
	}
	return (0);
}

/**
 * seek_path - finds this cmd in the PATH string
 * @data: data struct
 * @path_str: PATH string
 * @cmd: cmd to find
 * Return: full path of cmd if found or NULL
 */
char *seek_path(pass_args_t *data, char *path_str, char *cmd)
{
	int i = 0, current = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((strlen(cmd) > 2) && begins_with(cmd, "./"))
	{
		if (is_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_char(path_str, current, i);
			if (!*path)
				strcat(path, cmd);
			else
			{
				strcat(path, "/");
				strcat(path, cmd);
			}
			if (is_cmd(data, path))
				return (path);
			if (!path_str[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}
