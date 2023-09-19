#include "shell.h"
/**
 * chain_buffer - buffers chained commands
 * @data: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t chain_buffer(pass_args_t *data, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* fill buffer if empty */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigIntHandler);
#if USE_GETLINE

#else
		r = _getline(data, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			data->flag_Line_Count = 1;
			erase_comment(*buf);
			*len = r;
			data->cmd_buffer = buf;
		}
	}
	return (r);
}

/**
 * getInput - gets a line minus the newline
 * @data: parameter struct
 * Return: bytes read
 */
ssize_t getInput(pass_args_t *data)
{
	static char *buf; /* the ';' chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buff = &(data->arg_c), *ptr;

	_putchar(BUFFER_FLUSH);
	r = chain_buffer(data, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i; 
		ptr = buf + i; 

		while (j < len) 
		{
			if (chain_deli(data, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0; 
			data->buffer_type = _NORMAL;
		}

		*buff = ptr;
		return (strlen(ptr)); 
	}

	*buff = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @data: struct
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buf(pass_args_t *data, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(data->readfhand, buf, READ_BUFFER);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @data: parameter struct
 * @_ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(pass_args_t *data, char **_ptr, size_t *length)
{
	static char buf[READ_BUFFER];
	static size_t i, len;
	size_t j;
	ssize_t r = 0, s = 0;
	char *ptr = NULL, *new_p = NULL, *c;

	ptr = *_ptr;
	if (ptr && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(data, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strchr(buf + i, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(ptr, s, s ? s + j : j + 1);
	if (!new_p)
		return (ptr ? free(ptr), -1 : -1);

	if (s)
		strncat(new_p, buf + i, j - i);
	else
		strncpy(new_p, buf + i, j - i + 1);

	s += j - i;
	i = j;
	ptr = new_p;

	if (length)
		*length = s;
	*_ptr = ptr;
	return (s);
}

/**
 * sigIntHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigIntHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
