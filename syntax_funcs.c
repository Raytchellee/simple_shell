#include "main.h"

/**
 * char_count - counts character occurrences
 * @str: string to check
 * @idx: value of idx
 * Return: count
 */

int char_count(char *str, int idx)
{
	if (*(str - 1) == *str)
		return (char_count(str - 1, idx + 1));
	return (idx);
}

/**
 * sytx_err_check - finds and prints error
 * @cli_frame: input data
 * @str: string to check
 * Return: 0 or 1 if there is an error
 */

int sytx_err_check(cli_data *cli_frame, char *str)
{
	int start, find_c = 0, idx = 0;

	find_c = find_first_idx(str, &start);
	if (find_c == -1)
	{
		sytx_err_print(cli_frame, str, start, 0);
		return (1);
	}

	idx = find_sytx_err(str + start, 0, *(str + start));
	if (idx != 0)
	{
		sytx_err_print(cli_frame, str, start + idx, 1);
		return (1);
	}
	return (0);
}

/**
 * find_sytx_err - checks for syntax errors
 * @str: string to check
 * @idx: value of idx
 * @end: value of last charcter read
 * Return: 0 or index of error
 */
int find_sytx_err(char *str, int idx, char end)
{
	int len = 0;

	if (*str == '\0')
		return (0);

	if (*str == '\t' || *str == ' ')
		return (find_sytx_err(str + 1, idx + 1, end));

	if (*str == ';')
		if (end == ';' || end == '|' || end == '&')
			return (idx);

	if (*str == '|')
	{
		if (end == '&' || end == ';')
			return (idx);

		if (end == '|')
		{
			len = char_count(str, 0);
			if (len > 1 || len == 0)
				return (idx);
		}
	}

	if (*str == '&')
	{
		if (end == '|' || end == ';')
			return (idx);

		if (end == '&')
		{
			len = char_count(str, 0);
			if (len == 0 || len > 1)
				return (idx);
		}
	}
	return (find_sytx_err(str + 1, idx + 1, *str));
}

/**
 * find_first_idx - checks for idx of first occurrence of a char
 * @str: string to check
 * @idx: value of idx
 * Return: 0 or index of first occurence
 */

int find_first_idx(char *str, int *idx)
{
	for (*idx = 0; str[*idx]; *idx += 1)
	{
		if (str[*idx] == '\t' || str[*idx] == ' ')
			continue;

		if (str[*idx] == '|' || str[*idx] == '&' || str[*idx] == ';')
			return (-1);
		break;
	}
	return (0);
}

/**
 * sytx_err_print - prints syntax error message
 * @cli_frame: data
 * @str: string to check
 * @idx: error index
 * @check: confirm msg to output
 * Return: none
 */

void sytx_err_print(cli_data *cli_frame, char *str, int idx, int check)
{
	char *first, *sec, *third;
	char *msg_e, *tab;
	int count;

	if (str[idx] == ';')
	{
		if (check == 0)
			first = (str[idx + 1] == ';' ? ";;" : ";");
		else
			first = (str[idx - 1] == ';' ? ";;" : ";");
	}
	if (str[idx] == '|')
		first = (str[idx + 1] == '|' ? "||" : "|");

	if (str[idx] == '&')
		first = (str[idx + 1] == '&' ? "&&" : "&");

	third = "\" unexpected\n";
	sec = ": Syntax error: \"";
	tab = _to_string(cli_frame->count);
	count = _strlen(cli_frame->arg_v[0]) + _strlen(tab);
	count += 2 + _strlen(third) + _strlen(sec) + _strlen(first);

	msg_e = malloc((1 + count) * sizeof(char));
	if (msg_e == 0)
	{
		free(tab);
		return;
	}
	_strcpy(msg_e, cli_frame->arg_v[0]);
	_strcat(msg_e, ": ");
	_strcat(msg_e, tab);
	_strcat(msg_e, sec);
	_strcat(msg_e, first);
	_strcat(msg_e, "\" unexpected\n");
	_strcat(msg_e, "\0");
	write(STDERR_FILENO, msg_e, count);
	free(msg_e);
	free(tab);
}

