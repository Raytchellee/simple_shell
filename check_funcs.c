#include "main.h"

/**
 * str_to_var - substitutes str with variables
 * @hd: linked list head
 * @f_len: finished length
 * @str: str input
 * @str_new: string to replace
 * Return: string substituted
 */

char *str_to_var(variables_t **hd, char *str, char *str_new, int f_len)
{
	variables_t *item;
	int idx, idy, idz;

	item = *hd;
	for (idy = idx = 0; idx < f_len; idx++)
	{
		if (str[idy] == '$')
		{
			if (!(item->var_l) && !(item->val_l))
			{
				str_new[idx] = str[idy];
				idy++;
			}
			else if (item->var_l && !(item->val_l))
			{
				for (idz = 0; idz < item->var_l; idz++)
					idy++;
				idx--;
			}
			else
			{
				for (idz = 0; idz < item->val_l; idz++)
				{
					str_new[idx] = item->var_val[idz];
					idx++;
				}
				idy += (item->var_l);
				idx--;
			}
			item = item->next;
		}
		else
		{
			str_new[idx] = str[idy];
			idy++;
		}
	}

	return (str_new);
}

/**
 * str_var_func - calls appropriate function to replace str
 * @str: str input
 * @cli_frame: data
 * Return: string substituted
 */

char *str_var_func(char *str, cli_data *cli_frame)
{
	int len1, len2;
	char *str_new, *stats;
	variables_t *node, *item;

	stats = _to_string(cli_frame->status);
	node = NULL;
	len1 = confirm_var(&node, str, stats, cli_frame);

	if (node == NULL)
	{
		free(stats);
		return (str);
	}

	item = node;
	len2 = 0;

	while (item != NULL)
	{
		len2 += (item->val_l - item->var_l);
		item = item->next;
	}

	len2 += len1;
	str_new = malloc(sizeof(char) * (len2 + 1));
	str_new[len2] = '\0';

	str_new = str_to_var(&node, str, str_new, len2);

	free(str);
	free(stats);
	free_vars_t(&node);
	return (str_new);
}

/**
 * confirm_env - confirms env variables
 * @hd: linked list head
 * @str: str input
 * @data: data
 * Return: none
 */

void confirm_env(variables_t **hd, char *str, cli_data *data)
{
	int idx, col, idy, len;
	char **var_e;

	var_e = data->_environ;
	for (idx = 0; var_e[idx]; idx++)
	{
		for (idy = 1, col = 0; var_e[idx][col]; col++)
		{
			if (var_e[idx][col] == '=')
			{
				len = _strlen(var_e[idx] + col + 1);
				append_var(hd, idy, var_e[idx] + col + 1, len);
				return;
			}

			if (str[idy] == var_e[idx][col])
				idy++;
			else
				break;
		}
	}

	for (idy = 0; str[idy]; idy++)
	{
		if (str[idy] == '\n' || str[idy] == ' ' || str[idy] == ';' || str[idy] == '\t')
			break;
	}

	append_var(hd, idy, NULL, 0);
}

/**
 * confirm_var - confirm $? or $$ variable
 * @hd: linked list head
 * @s: str input
 * @stat: final shell status
 * @d: data
 * Return: none
 */

int confirm_var(variables_t **hd, char *s, char *stat, cli_data *d)
{
	int idx, len1, len2;

	len2 = _strlen(d->shell_id);
	len1 = _strlen(stat);

	for (idx = 0; s[idx]; idx++)
	{
		if (s[idx] == '$')
		{
			if (s[1 + idx] == '?')
				append_var(hd, 2, stat, len1), idx++;
			else if (s[1 + idx] == ';')
				append_var(hd, 0, NULL, 0);
			else if (s[1 + idx] == '$')
				append_var(hd, 2, d->shell_id, len2), idx++;
			else if (s[1 + idx] == '\t')
				append_var(hd, 0, NULL, 0);
			else if (s[1 + idx] == '\n')
				append_var(hd, 0, NULL, 0);
			else if (s[1 + idx] == ' ')
				append_var(hd, 0, NULL, 0);
			else if (s[1 + idx] == '\0')
				append_var(hd, 0, NULL, 0);
			else
				confirm_env(hd, s + idx, d);
		}
	}

	return (idx);
}



