#include "shell.h"

/**
 *puts_error - prints an input string
 * @str: string to be printed
 * Return: Nothing
 */
void puts_error(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putchar_error(str[i]);
		i++;
	}
}

/**
 * putchar_error - writes the character  to standard error
 * @c: haracter to print
 * Return: On success 1.
 */
int putchar_error(char c)
{
	static int i;
	static char buf[WRITE_BUFFER];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * fhand_put - writes the character c to given fhand
 * @c: character to print
 * @fd: file descriptor to write to
 * Return: On success 0, otherwise -1
 */
int fhand_put(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *fhand_puts - prints an input string
 * @str: string to be printed
 * @fd: file descriptor to write to
 * Return: number of chars put
 */
int fhand_puts(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += fhand_put(*str++, fd);
	}
	return (i);
}
