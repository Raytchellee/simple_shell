#include "main.h"

/**
 * free_struct - frees shell struct
 * @cli_frame: shell struct
 * Return: none
 */

void free_struct(cli_data *cli_frame)
{
	unsigned int idx;

	for (idx = 0; cli_frame->_env_var[idx]; idx++)
	{
		free(cli_frame->_env_var[idx]);
	}

	free(cli_frame->_env_var);
	free(cli_frame->shell_id);
}

/**
 * set_struct - sets shell struct
 * @cli_frame: shell struct
 * @arg_v: arg vector
 * Return: none
 */

void set_struct(cli_data *cli_frame, char **arg_v)
{
	unsigned int idx = 0;

	cli_frame->arg_v = arg_v;
	cli_frame->count = 1;
	cli_frame->status = 0;
	cli_frame->input = NULL;
	cli_frame->arguments = NULL;

	while (environ[idx])
		idx++;

	cli_frame->_env_var = malloc(sizeof(char *) * (idx + 1));

	for (idx = 0; environ[idx]; idx++)
	{
		cli_frame->_env_var[idx] = _strdup(environ[idx]);
	}

	cli_frame->_env_var[idx] = NULL;
	cli_frame->shell_id = _to_string(getpid());
}

/**
 * main - Entry function
 * @arg_c: argument count
 * @arg_v: argument vector
 * Return: 0 if successful
 */

int main(int arg_c, char **arg_v)
{
	cli_data cli_frame;
	(void) arg_c;

	signal(SIGINT, hndl_ctrl_c);
	set_struct(&cli_frame, arg_v);
	itr_cmd_l(&cli_frame);
	free_struct(&cli_frame);
	if (cli_frame.status < 0)
		return (255);
	return (cli_frame.status);
}

