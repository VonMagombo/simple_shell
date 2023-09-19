#include "shell.h"
/**
 *_puts - prints an input string
 *@str: string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - writes character to stdout
 * @c: character to print
 * Return: 1 on success.
 */
int _putchar(char c)
{
	static int j;
	static char buffer[WRITE_BUFFER];

	if (c == BUFFER_FLUSH || j >= WRITE_BUFFER)
	{
		write(1, buffer, j);
		j = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[j++] = c;
	return (1);
}
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * begins_with - checks if pin starts with stack
 * @stack: string to search
 * @pin: substring to find
 * Return: address of next char of stack or NULL
 */
char *begins_with(const char *stack, const char *pin)
{
	while (*pin)
		if (*pin++ != *stack++)
			return (NULL);
	return ((char *)stack);
}
