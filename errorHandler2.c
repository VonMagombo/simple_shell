#include "shell.h"
/**
 * atoi_err - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int atoi_err(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - prints an error message
 * @data: the parameter
 * @error: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise -1
 */
void print_err(pass_args_t *data, char *error)
{
	puts_error(data->fname);
	puts_error(": ");
	print_dec(data->line_count, STDERR_FILENO);
	puts_error(": ");
	puts_error(data->av[0]);
	puts_error(": ");
	puts_error(error);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @value: the value
 * @fhand: the filedescriptor to write to
 * Return: number of characters printed
 */
int print_dec(int value, int fhand)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fhand == STDERR_FILENO)
		__putchar = putchar_error;
	if (value < 0)
	{
		_abs_ = -value;
		__putchar('-');
		count++;
	}
	else
		_abs_ = value;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * itoa_rep - a replica of itoa converter
 * @num: number
 * @base: argument
 * @flags: argument flags
 * Return: string
 */
char *itoa_rep(long int num, int base, int flags)
{
	static char *array;
	static char buffer[60];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & _UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & SMALLCAPS ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[52];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * erase_comment - function replaces first instance of '#' with '\0'
 * @ptr: address of the string to modify
 * Return: Always 0;
 */
void erase_comment(char *ptr)
{
	int i;

	for (i = 0; ptr[i] != '\0'; i++)
		if (ptr[i] == '#' && (!i || ptr[i - 1] == ' '))
		{
			ptr[i] = '\0';
			break;
		}
}

