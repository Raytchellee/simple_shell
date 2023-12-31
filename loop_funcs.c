#include "main.h"

/**
 * rm_commnt - deletes input comments
 * @str: str input
 * Return: string with removed comment
 */

char *rm_commnt(char *str)
{
	int idx, count;

	count = 0;
	for (idx = 0; str[idx]; idx++)
	{
		if (str[idx] == '#')
		{
			if (idx == 0)
			{
				free(str);
				return (NULL);
			}

			if (str[idx - 1] == ' ' || str[idx - 1] == '\t' || str[idx - 1] == ';')
				count = idx;
		}
	}

	if (count != 0)
	{
		str = _realloc(str, idx, count + 1);
		str[count] = '\0';
	}

	return (str);
}

/**
 * itr_cmd_l - loops through the command line
 * @cli_frame: input data
 * Return: none
 */

void itr_cmd_l(cli_data *cli_frame)
{
	int count, last;
	char *str;

	count = 1;
	while (count == 1)
	{
		write(STDIN_FILENO, ": ) ", 4);
		str = read_in_str(&last);
		if (last != -1)
		{
			str = rm_commnt(str);
			if (str == NULL)
				continue;

			if (sytx_err_check(cli_frame, str) == 1)
			{
				cli_frame->status = 2;
				free(str);
				continue;
			}
			str = str_var_func(str, cli_frame);
			count = sep_cmdl(cli_frame, str);
			cli_frame->count += 1;
			free(str);
		}
		else
		{
			count = 0;
			free(str);
		}
	}
}

/**
 * main_cd - change dir
 * @cli_frame: input data
 * Return: 1 if pass
 */

int main_cd(cli_data *cli_frame)
{
	int chek1, check2, check_symb;
	char *wd;

	wd = cli_frame->arguments[1];

	if (wd != NULL)
	{
		check_symb = _strcmp("--", wd);
		check2 = _strcmp("~", wd);
		chek1 = _strcmp("$HOME", wd);
	}
	if (wd == NULL || !check_symb || !check2 || !chek1)
	{
		cd_home_dir(cli_frame);
		return (1);
	}
	if (_strcmp("-", wd) == 0)
	{
		cd_before(cli_frame);
		return (1);
	}
	if (_strcmp("..", wd) == 0 || _strcmp(".", wd) == 0)
	{
		cd_parent(cli_frame);
		return (1);
	}

	cd_dir(cli_frame);
	return (1);
}
