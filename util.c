#include "shell_2.h"

/**
 * free_dub - frees a double poiunter
 * @dub: double pointer passed
 */
void free_dub(char **dub)
{
	unsigned int i = 0;

	if (!dub)
		return;
	while (dub[i])
	{
		free(dub);
		i++;
	}
	if (dub[i] == NULL)
		free(dub[i]);
	free(dub);
}

