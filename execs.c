#include "shell_2.h"
int permission_denial(char **argv, char *cmd, int count);
int cmd_notfound(char **argv, char *cmd, int count);
/**
 * exarg - executes argument passed
 * @input: argument to execute
 * @env: env passed through
 * @count: count of prompt cycles
 * @argv: array of arguments
 * Return: 1 on success
 */
int exarg(char *input, char **env, int count, char **argv)
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
			exec_res = execve(chargv[0], chargv, env);
			if (exec_res < 0)
			{
				permission_denial(argv, chargv[0], count);
				return (127);
			}
			exit(EXIT_FAILURE);
		}
		else
			exec_path(chargv, input, env, count, argv);
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
	if (status == 139)
		status = 127;
	return (status);
}
/**
 * exec_path - executes when given pathless cmd
 * @chargv: argument array
 * @input: command given
 * @env: env passed
 * @count: count of prompt cycles
 * @argv: array of arguments
 */
void exec_path(char **chargv, char *input, char **env, int count, char **argv)
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
	cmd_notfound(argv, chargv[0], count);
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
