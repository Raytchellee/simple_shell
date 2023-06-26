#include "main.h"

/**
 * check_env_v - checks for env variables
 * @var_e: env variable name
 * @str: name to check
 * Return: len if equal 0 if not
 */

int check_env_v(const char *var_e, const char *str)
{
	int idx;

	for (idx = 0; var_e[idx] != '='; idx++)
	{
		if (var_e[idx] != str[idx])
		{
			return (0);
		}
	}
	return (idx + 1);
}

/**
 * _env - prints env variables
 * @cli_frame: data
 * Return: 1 if pass
 */

int _env(cli_data *cli_frame)
{
	int idx, idy;

	for (idx = 0; cli_frame->_environ[idx]; idx++)
	{
		idy = 0;
		while (cli_frame->_environ[idx][idy])
			idy++;

		write(STDOUT_FILENO, cli_frame->_environ[idx], idy);
		write(STDOUT_FILENO, "\n", 1);
	}
	cli_frame->status = 0;

	return (1);
}

/**
 * _getenv - gets correct env variable
 * @cmd_name: name to check
 * @_environ: env variable
 * Return: env varible if found, NULL otherwise
 */

char *_getenv(const char *cmd_name, char **_environ)
{
	char *str;
	int idx, count;

	str = NULL;
	count = 0;

	for (idx = 0; _environ[idx]; idx++)
	{
		count = check_env_v(_environ[idx], cmd_name);
		if (count)
		{
			str = _environ[idx];
			break;
		}
	}
	return (str + count);
}
