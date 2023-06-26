#include "main.h"

/**
 * ccat_cd_err - concatss cd error message
 * @cli_frame: data
 * @in: input message
 * @msg_e: error message
 * @num: number of lines for counter
 * Return: appriopriate message
 */

char *ccat_cd_err(cli_data *cli_frame, char *in, char *msg_e, char *num)
{
	char *f;

	_strcpy(msg_e, cli_frame->arg_v[0]);
	_strcat(msg_e, ": ");
	_strcat(msg_e, num);
	_strcat(msg_e, ": ");
	_strcat(msg_e, cli_frame->arguments[0]);
	_strcat(msg_e, in);
	if (cli_frame->arguments[1][0] == '-')
	{
		f = malloc(3);
		f[0] = '-';
		f[1] = cli_frame->arguments[1][1];
		f[2] = '\0';
		_strcat(msg_e, f);
		free(f);
	}
	else
	{
		_strcat(msg_e, cli_frame->arguments[1]);
	}

	_strcat(msg_e, "\n");
	_strcat(msg_e, "\0");

	return (msg_e);
}

/**
 * cd_error - cd command error message
 * @cli_frame: data
 * Return: appriopriate message
 */

char *cd_error(cli_data *cli_frame)
{
	int count, n;
	char *msg_e, *num, *in;

	num = _to_string(cli_frame->count);
	if (cli_frame->arguments[1][0] == '-')
	{
		in = ": Illegal option ";
		n = 2;
	}
	else
	{
		in = ": can't cd to ";
		n = _strlen(cli_frame->arguments[1]);
	}

	count = _strlen(cli_frame->arg_v[0]) + _strlen(cli_frame->arguments[0]);
	count += _strlen(in) + _strlen(num) + n + 5;
	msg_e = malloc(sizeof(char) * (count + 1));

	if (msg_e == 0)
	{
		free(num);
		return (NULL);
	}

	msg_e = ccat_cd_err(cli_frame, in, msg_e, num);

	free(num);

	return (msg_e);
}

/**
 * cmd_not_found - 'command no found' error message
 * @cli_frame: data
 * Return: appriopriate message
 */

char *cmd_not_found(cli_data *cli_frame)
{
	int count;
	char *msg_e, *num;

	num = _to_string(cli_frame->count);
	count = _strlen(cli_frame->arg_v[0]) + _strlen(num);
	count += _strlen(cli_frame->arguments[0]) + 16;
	msg_e = malloc(sizeof(char) * (count + 1));
	if (msg_e == 0)
	{
		free(msg_e);
		free(num);
		return (NULL);
	}
	_strcpy(msg_e, cli_frame->arg_v[0]);
	_strcat(msg_e, ": ");
	_strcat(msg_e, num);
	_strcat(msg_e, ": ");
	_strcat(msg_e, cli_frame->arguments[0]);
	_strcat(msg_e, ": not found\n");
	_strcat(msg_e, "\0");
	free(num);
	return (msg_e);
}

/**
 * exit_error - 'exit' error message
 * @cli_frame: data
 * Return: appriopriate message
 */

char *exit_error(cli_data *cli_frame)
{
	int count;
	char *msg_e, *num;

	num = _to_string(cli_frame->count);
	count = _strlen(cli_frame->arg_v[0]) + _strlen(num);
	count += 23 + _strlen(cli_frame->arguments[0]) + _strlen(cli_frame->arguments[1]);
	msg_e = malloc((count + 1) * sizeof(char));
	if (msg_e == 0)
	{
		free(num);
		return (NULL);
	}
	_strcpy(msg_e, cli_frame->arg_v[0]);
	_strcat(msg_e, ": ");
	_strcat(msg_e, num);
	_strcat(msg_e, ": ");
	_strcat(msg_e, cli_frame->arguments[0]);
	_strcat(msg_e, ": Illegal digit: ");
	_strcat(msg_e, cli_frame->arguments[1]);
	_strcat(msg_e, "\n\0");
	free(num);
	return (msg_e);
}
