#include "main.h"

/**
 * assign_line - passes line variables to read_input
 * @ptr_str: store the input str
 * @str: called string
 * @l: line size
 * @b: buffer size
 */

void assign_line(char **ptr_str, size_t *l, char *str, size_t b)
{

	if (*ptr_str == NULL)
	{
		if  (b > BUFF_SIZE)
			*l = b;

		else
			*l = BUFF_SIZE;
		*ptr_str = str;
	}
	else if (*l < b)
	{
		if (b > BUFF_SIZE)
			*l = b;
		else
			*l = BUFF_SIZE;
		*ptr_str = str;
	}
	else
	{
		_strcpy(*ptr_str, str);
		free(str);
	}
}

/**
 * read_input - Reads lines from input stream
 * @ptr_str: store the input str
 * @l: ptr_str size
 * @p_strm: passed stream
 * Return: byte number
 */

ssize_t read_input(char **ptr_str, size_t *l, FILE *p_strm)
{
	static ssize_t entry;
	ssize_t res;
	char *str;
	char c = 'z';
	int idx;

	if (entry == 0)
		fflush(p_strm);
	else
		return (-1);
	entry = 0;

	str = malloc(sizeof(char) * BUFF_SIZE);
	if (str == 0)
		return (-1);
	while (c != '\n')
	{
		idx = read(STDIN_FILENO, &c, 1);
		if (idx == -1 || (idx == 0 && entry == 0))
		{
			free(str);
			return (-1);
		}
		if (idx == 0 && entry != 0)
		{
			entry++;
			break;
		}
		if (entry >= BUFF_SIZE)
			str = _realloc(str, entry, entry + 1);
		str[entry] = c;
		entry++;
	}
	str[entry] = '\0';
	assign_line(ptr_str, l, str, entry);
	res = entry;
	if (idx != 0)
		entry = 0;
	return (res);
}

/**
 * check_builtin - checks for commands/builtin functions
 * @cli_frame: data
 * Return: 1 if pass
 */

int check_builtin(cli_data *cli_frame)
{
	int (*bltn_val)(cli_data *cli_frame);

	if (cli_frame->arguments[0] == NULL)
		return (1);

	bltn_val = find_builtn(cli_frame->arguments[0]);

	if (bltn_val != NULL)
		return (bltn_val(cli_frame));

	return (exec_cmd_line(cli_frame));
}

/**
 * find_builtn - passes command to arguments
 * @cmmnd: the command
 * Return: builtin pointer function
 */

int (*find_builtn(char *cmmnd))(cli_data *)
{
	built_in_t bltn_val[] = {
		{ "help", rtrv_help_msg },
		{ "env", _env },
		{ "exit", main_exit },
		{ "cd", main_cd },
		{ "setenv", cmp_env },
		{ "unsetenv", rm_env },
		{ NULL, NULL }
	};
	int idx;

	for (idx = 0; bltn_val[idx].cmd_name; idx++)
	{
		if (_strcmp(bltn_val[idx].cmd_name, cmmnd) == 0)
			break;
	}

	return (bltn_val[idx].func);
}

/**
 * rtrv_help_msg - gets help message
 * @cli_frame: data
 * Return: 0
*/

int rtrv_help_msg(cli_data *cli_frame)
{

	if (cli_frame->arguments[1] == 0)
		builtin_help();
	else if (_strcmp(cli_frame->arguments[1], "help") == 0)
		help_info();
	else if (_strcmp(cli_frame->arguments[1], "env") == 0)
		bltn_env_help();
	else if (_strcmp(cli_frame->arguments[1], "setenv") == 0)
		cmp_env_help();
	else if (_strcmp(cli_frame->arguments[1], "exit") == 0)
		bltn_exit_help();
	else if (_strcmp(cli_frame->arguments[1], "alias") == 0)
		alias_help_info();
	else if (_strcmp(cli_frame->arguments[1], "cd") == 0)
		cd_help_info();
	else if (_strcmp(cli_frame->arguments[1], "unsetenv") == 0)
		rm_env_help();
	else
		write(STDERR_FILENO, cli_frame->arguments[0],
			_strlen(cli_frame->arguments[0]));

	cli_frame->status = 0;
	return (1);
}
