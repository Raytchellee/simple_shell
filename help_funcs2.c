#include "main.h"

/**
 * help_info - 'help' help info
 * Return: none
 */

void help_info(void)
{
	char *text = "help: usage help [-dms] [pattern ...]\n\t";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "You can view information for built-ins commands.\n ";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "You can view brief summaries of bash built-ins.\n";
	write(STDOUT_FILENO, text, _strlen(text));
}

/**
 * alias_help_info - 'alias' help info
 * Return: none
 */

void alias_help_info(void)
{
	char *text = "alias: usage alias [-p] [name[=value]...]\n\t";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "You can either define or display aliases.\n ";
	write(STDOUT_FILENO, text, _strlen(text));
}

/**
 * cd_help_info - 'cd' help info
 * Return: none
 */

void cd_help_info(void)
{
	char *text = "cd: usage cd [-L|[-P [-e]] [-@]] [dir]\n\t";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "Change current working directory to specified location\n ";
	write(STDOUT_FILENO, text, _strlen(text));
}

