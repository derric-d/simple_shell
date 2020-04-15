#include "shell_2.h"
/**
 * path_error - handles error for path cmd
 * @chargv: argument vector
 * @cmd: cmd passed
 * @count: count of prompt cycles
 */
void path_error(char **chargv, char *cmd, int count)
{
	(void)chargv;
	(void)count;

	write(1, cmd, _strlen(cmd));
	write(1, ": command not found\n", 20);

}
/**
 * exarg - executes argument passed
 * @input: argument to execute
 * @env: env passed through
 * @count: count of prompt cycles
 * Return: 1 on success
 */
int exarg(char *input, char **env, int count)
{
	pid_t pid;
	int status = 1, exec_res;
	struct stat filestat;
	char **chargv;

	pid = fork();
	if (pid == 0)
	{
		get_tokens(input, BLANK_STRING, &chargv);
		if (chargv == NULL)
		{
			free(input);
			input = NULL;
			exit(EXIT_SUCCESS);
		}
		else if (_strcmp("env", chargv[0]) == 0)
			exec_env(input, chargv, env);
		else if (stat(chargv[0], &filestat) == 0)
		{
			exec_res = execve(chargv[0], chargv, NULL);
			if (exec_res < 0)
				perror("exec error");
			exit(EXIT_FAILURE);
		}
		else
		{
			exec_path(chargv, input, env, count);
		}
	}
	else if (pid < 0)
	{
		perror("forking err");
	}
	else
	{
		do {
			wait(&status);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (status);
}
/**
 * exec_path - executes when given pathless cmd
 * @chargv: argument array
 * @input: command given
 * @env: env passed
 * @count: count of prompt cycles
 */
void exec_path(char **chargv, char *input, char **env, int count)
{
	struct stat pathstat;
	int i = 0;
	char **pathdirs;

	pathdirs = env_array(chargv[0], env);
	while (pathdirs[i])
	{
		if (stat(pathdirs[i], &pathstat) == 0)
			execve(pathdirs[i], chargv, NULL);
		i++;
	}
	path_error(chargv, chargv[0], count);

	free(input);
	input = NULL;
	free_dub(chargv);
	chargv = NULL;
	free_dub(pathdirs);
	pathdirs = NULL;
	exit(EXIT_SUCCESS);
}
/**
 * eof_routine - handles eof
 * @line: argument passed
 */
void eof_routine(char *line)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(line);
	line = NULL;
	exit(0);
}


