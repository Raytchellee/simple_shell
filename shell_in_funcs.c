#include "main.h"

/**
 * read_in_str - reads string from input
 * @last: getline return value
 * Return: string value
 */

char *read_in_str(int *last)
{
	char *str = NULL;
	size_t size_of_buf = 0;

	*last = getline(&str, &size_of_buf, stdin);

	return (str);
}

/**
 * main_exit - shell exit function
 * @cli_frame: input data
 * Return: 0 if pass
 */

int main_exit(cli_data *cli_frame)
{
	unsigned int stat_check;
	int check_num, len, is_large;

	if (cli_frame->arguments[1] != NULL)
	{
		stat_check = _atoi(cli_frame->arguments[1]);
		check_num = _isdigit(cli_frame->arguments[1]);
		len = _strlen(cli_frame->arguments[1]);
		is_large = stat_check > (unsigned int)INT_MAX;
		if (len > 10 || !check_num || is_large)
		{
			call_error(cli_frame, 2);
			cli_frame->status = 2;
			return (1);
		}
		cli_frame->status = (stat_check % 256);
	}
	return (0);
}

/**
 * hndl_ctrl_c - takes care of the 'ctrl + C' call
 * @signal: handles signal
 */

void hndl_ctrl_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n: ) ", 5);
}

