#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define TOKEN_BUFF 128
#define TOKEN_DELIM " \t\r\n\a"
#define BUFF_SIZE 1024

/* pointer to array of pointers to the environment strings */
extern char **environ;

/**
 * struct cli_in - structure to hold shell runtime data
 * @arguments: command line tokens
 * @arg_v: arg vector
 * @input: user input
 * @_env_var: environmental variables
 * @count: count of lines read
 * @shell_id:  shell process id
 * @status: updated shell status
 */

typedef struct cli_in
{
	char **arguments;
	char **arg_v;
	char *input;
	char **_env_var;
	int count;
	char *shell_id;
	int status;
} cli_data;



#endif

