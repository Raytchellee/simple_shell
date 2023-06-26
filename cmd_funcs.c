#include "main.h"

/**
 * check_curr - confirms whether ':' is in current dir
 * @pp: pointher to path
 * @idx: pointer to index
 * Return: 1 if successful 0 if not
 */

int check_curr(char *pp, int *idx)
{
	if (pp[*idx] == ':')
		return (1);
	while (pp[*idx] != ':' && pp[*idx])
	{
		*idx += 1;
	}
	if (pp[*idx])
		*idx += 1;
	return (0);
}

/**
 * find_cmd - finds a command
 * @commnd: cmd name
 * @_environ: env variable
 * Return: pointer to cmd
 */

char *find_cmd(char *commnd, char **_environ)
{
	struct stat stats;
	char *pp, *ppp, *p_tok, *wd;
	int count_d, count_c, idx;

	pp = _getenv("PATH", _environ);
	if (pp)
	{
		ppp = _strdup(pp);
		count_c = _strlen(commnd);
		p_tok = _strtok(ppp, ":");
		idx = 0;
		while (p_tok != NULL)
		{
			if (check_curr(pp, &idx))
				if (stat(commnd, &stats) == 0)
					return (commnd);
			count_d = _strlen(p_tok);
			wd = malloc(2 + count_c + count_d);
			_strcpy(wd, p_tok);
			_strcat(wd, "/");
			_strcat(wd, commnd);
			_strcat(wd, "\0");
			if (stat(wd, &stats) == 0)
			{
				free(ppp);
				return (wd);
			}
			free(wd);
			p_tok = _strtok(NULL, ":");
		}
		free(ppp);
		if (stat(commnd, &stats) == 0)
			return (commnd);
		return (NULL);
	}
	if (commnd[0] == '/')
		if (stat(commnd, &stats) == 0)
			return (commnd);
	return (NULL);
}

/**
 * check_exec - confirms if data is executable
 * @cli_frame: data
 * Return: appripraite number if execusionable, 0 otherwise
 */

int check_exec(cli_data *cli_frame)
{
	struct stat stats;
	char *str;
	int idx;

	str = cli_frame->arguments[0];
	for (idx = 0; str[idx]; idx++)
	{
		if (str[idx] == '.')
		{
			if (str[1 + idx] == '.')
				return (0);
			if (str[1 + idx] == '/')
				continue;
			else
				break;
		}
		else if (str[idx] == '/' && idx != 0)
		{
			if (str[1 + idx] == '.')
				continue;
			idx++;
			break;
		}
		else
			break;
	}
	if (idx == 0)
		return (0);

	if (stat(str + idx, &stats) == 0)
	{
		return (idx);
	}
	call_error(cli_frame, 127);

	return (-1);
}

/**
 * verify_access - confirms user access
 * @wd: directory to confirm access for
 * @cli_frame: data
 * Return: 0 if successful or 1 otherwise
 */

int verify_access(char *wd, cli_data *cli_frame)
{
	if (wd == NULL)
	{
		call_error(cli_frame, 127);
		return (1);
	}
	if (_strcmp(cli_frame->arguments[0], wd) != 0)
	{
		if (access(wd, X_OK) == -1)
		{
			call_error(cli_frame, 126);
			free(wd);
			return (1);
		}
		free(wd);
	}
	else
	{
		if (access(cli_frame->arguments[0], X_OK) == -1)
		{
			call_error(cli_frame, 126);
			return (1);
		}
	}
	return (0);
}

/**
 * exec_cmd_line - executes the cmd line
 * @cli_frame: data
 * Return: 1 if pass
 */

int exec_cmd_line(cli_data *cli_frame)
{
	char *pth;
	pid_t pr_id, id_wait;
	int check, conf;
	(void) id_wait;

	conf = check_exec(cli_frame);
	if (conf == -1)
		return (1);
	if (conf == 0)
	{
		pth = find_cmd(cli_frame->arguments[0], cli_frame->_environ);
		if (verify_access(pth, cli_frame) == 1)
			return (1);
	}
	pr_id = fork();
	if (pr_id == 0)
	{
		if (conf == 0)
			pth = find_cmd(cli_frame->arguments[0], cli_frame->_environ);
		else
			pth = cli_frame->arguments[0];
		execve(pth + conf, cli_frame->arguments, cli_frame->_environ);
	}
	else if (pr_id < 0)
	{
		perror(cli_frame->arg_v[0]);
		return (1);
	}
	else
	{
		do {
			id_wait = waitpid(pr_id, &check, WUNTRACED);
		} while (!WIFEXITED(check) && !WIFSIGNALED(check));
	}
	cli_frame->status = check / 256;

	return (1);
}

