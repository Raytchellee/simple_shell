#include "main.h"

/**
 * cd_home_dir - switches to home dir
 * @cli_frame: data
 * Return: none
 */

void cd_home_dir(cli_data *cli_frame)
{
	char *dir_h, *w_dir;
	char dir_path[PATH_MAX];

	getcwd(dir_path, sizeof(dir_path));
	w_dir = _strdup(dir_path);

	dir_h = _getenv("HOME", cli_frame->_environ);

	if (dir_h == NULL)
	{
		env_var_set("OLDPWD", w_dir, cli_frame);
		free(w_dir);
		return;
	}

	if (chdir(dir_h) == -1)
	{
		call_error(cli_frame, 2);
		free(w_dir);
		return;
	}

	env_var_set("OLDPWD", w_dir, cli_frame);
	env_var_set("PWD", dir_h, cli_frame);
	free(w_dir);
	cli_frame->status = 0;
}

/**
 * cd_parent - switch to parent directory
 * @cli_frame: cmd data
 * Return: none
 */

void cd_parent(cli_data *cli_frame)
{
	char *curr_dir, *p_dir, *dir_tok;
	char dir_path[PATH_MAX];

	getcwd(dir_path, sizeof(dir_path));
	p_dir = _strdup(dir_path);
	env_var_set("OLDPWD", p_dir, cli_frame);
	curr_dir = cli_frame->arguments[1];
	if (_strcmp(".", curr_dir) == 0)
	{
		env_var_set("PWD", p_dir, cli_frame);
		free(p_dir);
		return;
	}
	if (_strcmp("/", p_dir) == 0)
	{
		free(p_dir);
		return;
	}
	dir_tok = p_dir;
	str_revrse(dir_tok);
	dir_tok = _strtok(dir_tok, "/");
	if (dir_tok != NULL)
	{
		dir_tok = _strtok(NULL, "\0");

		if (dir_tok != NULL)
			str_revrse(dir_tok);
	}
	if (dir_tok != NULL)
	{
		chdir(dir_tok);
		env_var_set("PWD", dir_tok, cli_frame);
	}
	else
	{
		chdir("/");
		env_var_set("PWD", "/", cli_frame);
	}
	cli_frame->status = 0;
	free(p_dir);
}

/**
 * cd_dir - switch to given directory
 * @cli_frame: data
 * Return: none
 */

void cd_dir(cli_data *cli_frame)
{
	char *curr_dir, *w_dir, *g_dir;
	char dir_path[PATH_MAX];

	getcwd(dir_path, sizeof(dir_path));

	curr_dir = cli_frame->arguments[1];
	if (chdir(curr_dir) == -1)
	{
		call_error(cli_frame, 2);
		return;
	}

	w_dir = _strdup(dir_path);
	env_var_set("OLDPWD", w_dir, cli_frame);

	g_dir = _strdup(curr_dir);
	env_var_set("PWD", g_dir, cli_frame);

	free(w_dir);
	free(g_dir);

	cli_frame->status = 0;
	chdir(curr_dir);
}

/**
 * cd_before - switches to prev directory
 * @cli_frame: data
 * Return: none
 */

void cd_before(cli_data *cli_frame)
{
	char *dir_p, *dir_old_p, *dir_g, *old_dir_g;
	char curr_dir[PATH_MAX];

	getcwd(curr_dir, sizeof(curr_dir));
	dir_g = _strdup(curr_dir);

	dir_old_p = _getenv("OLDPWD", cli_frame->_environ);

	if (dir_old_p == NULL)
		old_dir_g = dir_g;
	else
		old_dir_g = _strdup(dir_old_p);

	env_var_set("OLDPWD", dir_g, cli_frame);

	if (chdir(old_dir_g) == -1)
		env_var_set("PWD", dir_g, cli_frame);
	else
		env_var_set("PWD", old_dir_g, cli_frame);

	dir_p = _getenv("PWD", cli_frame->_environ);

	write(STDOUT_FILENO, dir_p, _strlen(dir_p));
	write(STDOUT_FILENO, "\n", 1);

	free(dir_g);
	if (dir_old_p)
		free(old_dir_g);

	cli_frame->status = 0;
	chdir(dir_p);
}


