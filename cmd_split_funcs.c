#include "main.h"

/**
 * str_swp - swaps & and | chars
 * @str: str input
 * @typ: type of swap
 * Return: the string swpped
 */

char *str_swp(char *str, int typ)
{
	int idx;

	if (typ == 0)
	{
		for (idx = 0; str[idx]; idx++)
		{
			if (str[idx] == '|')
			{
				if (str[idx + 1] != '|')
					str[idx] = 16;
				else
					idx++;
			}
			if (str[idx] == '&')
			{
				if (str[idx + 1] != '&')
					str[idx] = 12;
				else
					idx++;
			}
		}
	}
	else
	{
		for (idx = 0; str[idx]; idx++)
		{
			str[idx] = (str[idx] == 12 ? '&' : str[idx]);
			str[idx] = (str[idx] == 16 ? '|' : str[idx]);
		}
	}
	return (str);
}

/**
 * add_to_list - inludes cmd lines and sep to list
 * @sep_h: list for separators head
 * @list_h: cmd list head
 * @str: str input
 * Return: none
 */

void add_to_list(separators_t **sep_h, command_lines_t **list_h, char *str)
{
	char *s;
	int idx;

	str = str_swp(str, 0);
	for (idx = 0; str[idx]; idx++)
	{
		if (str[idx] == ';')
			append_sep(sep_h, str[idx]);

		if (str[idx] == '|' || str[idx] == '&')
		{
			append_sep(sep_h, str[idx]);
			idx++;
		}
	}

	s = _strtok(str, ";|&");
	do {
		s = str_swp(s, 1);
		append_cmdl(list_h, s);
		s = _strtok(NULL, ";|&");
	} while (s != NULL);

}

/**
 * next_cmd - goes to following stored cmd line
 * @sep_l: list for separators
 * @llist: list for cmd line
 * @cli_frame: data
 * Return: none
 */

void next_cmd(separators_t **sep_l, command_lines_t **llist, cli_data *cli_frame)
{
	command_lines_t *cmd_lt;
	separators_t *sep_lt;
	int count;

	count = 1;
	sep_lt = *sep_l;
	cmd_lt = *llist;

	while (sep_lt != NULL && count)
	{
		if (cli_frame->status == 0)
		{
			if (sep_lt->sep_value == ';' || sep_lt->sep_value == '&')
				count = 0;
			if (sep_lt->sep_value == '|')
				cmd_lt = cmd_lt->next, sep_lt = sep_lt->next;
		}
		else
		{
			if (sep_lt->sep_value == ';' || sep_lt->sep_value == '|')
				count = 0;
			if (sep_lt->sep_value == '&')
				cmd_lt = cmd_lt->next, sep_lt = sep_lt->next;
		}
		if (sep_lt != NULL && !count)
			sep_lt = sep_lt->next;
	}

	*sep_l = sep_lt;
	*llist = cmd_lt;
}

/**
 * sep_cmdl - divides cmd lines based on separators and rums them
 * @cli_frame: data
 * @str: str input
 * Return: 1 if yes, 0 if exit
 */

int sep_cmdl(cli_data *cli_frame, char *str)
{

	separators_t *sep_h, *sep_l;
	command_lines_t *list_h, *llist;
	int loop;

	sep_h = NULL;
	list_h = NULL;

	add_to_list(&sep_h, &list_h, str);

	sep_l = sep_h;
	llist = list_h;

	while (llist != NULL)
	{
		cli_frame->input = llist->curr_line;
		cli_frame->arguments = str_to_toks(cli_frame->input);
		loop = check_builtin(cli_frame);
		free(cli_frame->arguments);

		if (loop == 0)
			break;

		next_cmd(&sep_l, &llist, cli_frame);

		if (llist != NULL)
			llist = llist->next;
	}

	free_separators_t(&sep_h);
	free_command_lines_t(&list_h);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * str_to_toks - converts str input to tokens
 * @str: str input.
 * Return: tokenized string
 */

char **str_to_toks(char *str)
{
	char *one_tok;
	char **toks;
	size_t byt_s, idx;

	byt_s = TOKEN_BUFF;
	toks = malloc(sizeof(char *) * (byt_s));
	if (toks == NULL)
	{
		write(STDERR_FILENO, ": memory allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	one_tok = _strtok(str, TOKEN_DELIM);
	toks[0] = one_tok;

	for (idx = 1; one_tok != NULL; idx++)
	{
		if (idx == byt_s)
		{
			byt_s += TOKEN_BUFF;
			toks = realloc_dptr(toks, idx, sizeof(char *) * byt_s);
			if (toks == NULL)
			{
				write(STDERR_FILENO, ": memory allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		one_tok = _strtok(NULL, TOKEN_DELIM);
		toks[idx] = one_tok;
	}

	return (toks);
}

