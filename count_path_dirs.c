#include "shell_2.h"

/**
 * count_path_dir - counts path directories
 * @path: path passed
 * Return: count of directories
 */
unsigned int count_path_dir(char *path)
{
	unsigned int count, i, flag;

	i = count = flag = 0;

	while (path[i])
	{
		if (path[i] != ':')
			flag = 1;
		if ((flag && path[i + 1] == ':') || (flag && path[i + 1] == '\0'))
		{
			count++;
			flag = 0;
		}
		i++;
	}
	return (count);
}

