#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: pointer to memory area
 *@c: byte(s) to fill *s with
 *@n: amount of bytes to be filled
 *Return: a pointer to the memory area s
 */
char *_memset(char *s, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = c;
	return (s);
}

/**
 * free_up - frees up a pointer and assigns NULL to the address
 * @ptr: address of the pointer to be freed
 * Return: 1 if freed, otherwise 0.
 */
int free_up(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_str - frees strings
 * @pptr: string of strings
 */
void free_str(char **pptr)
{
	char **a = pptr;

	if (!pptr)
		return;
	while (*pptr)
		free(*pptr++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloced block
 * @former_size: size of previous block
 * @latest_size: latest_size of new block
 * Return: pointer to the former block name
 */
void *_realloc(void *ptr, unsigned int former_size, unsigned int latest_size)
{
	char *new_memory;

	if (!ptr)
		return (malloc(latest_size));
	if (!latest_size)
		return (free(ptr), NULL);
	if (latest_size == former_size)
		return (ptr);

	new_memory = malloc(latest_size);
	if (!new_memory)
		return (NULL);

	former_size = former_size < latest_size ? former_size : latest_size;
	while (former_size--)
		new_memory[former_size] = ((char *)ptr)[former_size];
	free(ptr);
	return (new_memory);
}
