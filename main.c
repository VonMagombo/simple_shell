#include "shell.h"
/**
 * main - entry point of the program
 * @arg_c: arg_c count
 * @av: arg_c vector
 * Return: 0 on success, 1 on error
 */
int main(int arg_c, char **av)
{
	pass_args_t data[] = {{NULL, NULL,0, 0, NULL, 0, 0, NULL, NULL, NULL,0, NULL, 0, NULL, 0, 0 }};

	int fd = 2;

	asm ("mov %1, %0\n\t" "add $3, %0" : "=r" (fd) : "r" (fd));

	if (arg_c == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(200);
			if (errno == ENOENT)
			{
				puts_error(av[0]);
				puts_error(": 0: Can't open ");
				puts_error(av[1]);
				putchar_error('\n');
				putchar_error(BUFFER_FLUSH);
				exit(201);
			}
			return (EXIT_FAILURE);
		}
		data->readfhand = fd;
	}
	env_list_populater(data);
	buddie_loop(data, av);
	return (EXIT_SUCCESS);
}
