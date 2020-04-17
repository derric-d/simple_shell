#include "shell_2.h"
/**
 * _perror - print to std error
 * @s: string to print
 * Return: bytes written
 */
void _perror(char *s)
{
	int i = 0;

	if (!s)
		return;

	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}
/**
 * _perror_int - write int to std error
 * @n: int to be written
 * Return: 0 on success
 */
void _perror_int(int n)
{
	char num;

	if ((n / 10) > 0)
		_perror_int(n / 10);

	num = n % 10 + '0';
	write(2, &num, 1);
}
/**
 * cmd_notfound - error message for commands
 * @argv: array of arguments from cmd line
 * @cmd: command passed as input
 * @count: count of commands
 * Return: 127 error code
 */
int cmd_notfound(char **argv, char *cmd, int count)
{
	_perror(argv[0]);
	_perror(": ");
	_perror_int(count);
	_perror(": ");
	_perror(cmd);
	_perror(": not found\n");

	return (127);
}
/**
 * permission_denial - error for perm denial
 * @argv: argument vector passed at rpogram start
 * @cmd: cmd passed as input
 * @count: count of commands
 * Return: 127 error code
 */
int permission_denial(char **argv, char *cmd, int count)
{
	_perror(argv[0]);
	_perror(": ");
	_perror_int(count);
	_perror(": ");
	_perror(cmd);
	_perror(": Permission denied\n");

	return (127);
}
