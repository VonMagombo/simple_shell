#include "shell.h"

/**
 * _strtok - splits a string into words.  repeats are ignored
 * @str: input string
 * @del: delimeter string
 * Return: a pointer to an array of strings otherwise NULL 
 */
char **_strtok(char *str, char *del)
{
	int i, j, n, m, word = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], del) && (is_delim(str[i + 1], del) || !str[i + 1]))
			word++;

	if (word == 0)
		return (NULL);
	s = malloc((1 + word) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < word; j++)
	{
		while (is_delim(str[i], del))
			i++;
		n = 0;
		while (!is_delim(str[i + n], del) && str[i + n])
			n++;
		s[j] = malloc((n + 1) * sizeof(char));
		if (!s[j])
		{
			for (n = 0; n < j; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < n; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}