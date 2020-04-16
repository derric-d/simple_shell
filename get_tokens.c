#include "shell_2.h"

/**
 * get_tokens - makes a tokenized array of arguments
 * @line: line to parse
 * @delimiters: characters to mark tokens
 * @argvp: argument array to populate
 * Return: number of tokens in list
 */
int get_tokens(char *line, const char *delimiters, char ***argvp)
{
	int error, i, numtokens = 0;
	char *t;
	const char *snew;

	line[_strlen(line) - 1] = '\0';
	if ((line == NULL) || (delimiters == NULL) || (argvp == NULL))
	{
		errno = EINVAL;
		return (-1);
	}
	*argvp = NULL;
	snew = line + _strspn(line, delimiters);
	t = malloc(_strlen(snew) + 1);
	if (t == NULL)
		return (-1);
	_strcpy(t, snew);
	if (strtok(t, delimiters) != NULL)
		for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++)
			;
	*argvp = malloc((numtokens + 1) * sizeof(char *));
	if (*argvp == NULL)
	{
		error = errno;
		free(t);
		t = NULL;
		errno = error;
		return (-1);
	}
	if (numtokens == 0)
		free(t);
	else
	{
		_strcpy(t, snew);
		**argvp = strtok(t, delimiters);
		for (i = 1; i < numtokens; i++)
			*((*argvp) + i) = strtok(NULL, delimiters);
	}
	*((argvp) + numtokens) = NULL;
	return (numtokens);
}

