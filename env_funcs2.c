#include "main.h"

/**
 * create_cpy - create info from already existing one
 * @item: alias or env name
 * @item_val: alias or env value
 * Return: new value
 */

char *create_cpy(char *item, char *item_val)
{
	int count1, count2, total;
	char *copy;

	count1 = _strlen(item);
	count2 = _strlen(item_val);
	total = count1 + count2 + 2;
	copy = malloc(sizeof(char) * (total));
	_strcpy(copy, item);
	_strcat(copy, "=");
	_strcat(copy, item_val);
	_strcat(copy, "\0");

	return (copy);
}

/**
 * env_var_set - sets env variable
 * @item: env variable name
 * @item_val: variable value
 * @cli_frame: data
 * Return: none
 */

void env_var_set(char *item, char *item_val, cli_data *cli_frame)
{
	int idx;
	char *env_v, *item_name;

	for (idx = 0; cli_frame->_environ[idx]; idx++)
	{
		env_v = _strdup(cli_frame->_environ[idx]);
		item_name = _strtok(env_v, "=");
		if (_strcmp(item_name, item) == 0)
		{
			free(cli_frame->_environ[idx]);
			cli_frame->_environ[idx] = create_cpy(item_name, item_val);
			free(env_v);
			return;
		}
		free(env_v);
	}

	cli_frame->_environ = realloc_dptr(cli_frame->_environ, idx, (2 + idx) * sizeof(char *));
	cli_frame->_environ[idx] = create_cpy(item, item_val);
	cli_frame->_environ[idx + 1] = NULL;
}

/**
 * cmp_env - checks passed env variable
 * @cli_frame: data
 * Return: 1 if pass
 */

int cmp_env(cli_data *cli_frame)
{

	if (cli_frame->arguments[1] == NULL || cli_frame->arguments[2] == NULL)
	{
		call_error(cli_frame, -1);
		return (1);
	}

	env_var_set(cli_frame->arguments[1], cli_frame->arguments[2], cli_frame);
	return (1);
}

/**
 * rm_env - removes env variable
 * @cli_frame: data
 * Return: 1 if pass
 */

int rm_env(cli_data *cli_frame)
{
	char **env_location;
	char *env_v, *item_name;
	int idx, idy, idz;

	if (cli_frame->arguments[1] == NULL)
	{
		call_error(cli_frame, -1);
		return (1);
	}
	idz = -1;
	for (idx = 0; cli_frame->_environ[idx]; idx++)
	{
		env_v = _strdup(cli_frame->_environ[idx]);
		item_name = _strtok(env_v, "=");
		if (_strcmp(item_name, cli_frame->arguments[1]) == 0)
		{
			idz = idx;
		}
		free(env_v);
	}
	if (idz == -1)
	{
		call_error(cli_frame, -1);
		return (1);
	}
	env_location = malloc(sizeof(char *) * (idx));
	for (idx = idy = 0; cli_frame->_environ[idx]; idx++)
	{
		if (idx != idz)
		{
			env_location[idy] = cli_frame->_environ[idx];
			idy++;
		}
	}
	env_location[idy] = NULL;
	free(cli_frame->_environ[idz]);
	free(cli_frame->_environ);
	cli_frame->_environ = env_location;
	return (1);
}

