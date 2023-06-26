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
 * @_environ: environmental variables
 * @count: count of lines read
 * @shell_id:  shell process id
 * @status: updated shell status
 */

typedef struct cli_in
{
	char **arguments;
	char **arg_v;
	char *input;
	char **_environ;
	int count;
	char *shell_id;
	int status;
} cli_data;

/**
 * struct built_in - structure for built in command
 * @cmd_name: name of built in command
 * @func: function pointer
 */

typedef struct built_in
{
	char *cmd_name;
	int (*func)(cli_data *cli_frame);
} built_in_t;


/**
 * struct command_lines - command lines linked list
 * @curr_line: current line
 * @next: next line
 * Description: stores all command line arguments
 */

typedef struct command_lines
{
	char *curr_line;
	struct command_lines *next;
} command_lines_t;

/**
 * struct separators_s - structure to store separators
 * @sep_value: seperator values
 * @next: next node
 * Description: list for separators
 */

typedef struct separators_s
{
	char sep_value;
	struct separators_s *next;
} separators_t;

/**
 * struct variables_s - linked list for variables
 * @var_l: variable length
 * @var_val: variable value
 * @val_l: value length
 * @next: next node
 * Description: list to store variables
 */

typedef struct variables_s
{
	int var_l;
	char *var_val;
	int val_l;
	struct variables_s *next;
} variables_t;


/* alloc_funcs.c */
char **realloc_dptr(char **old_ptr, unsigned int size1, unsigned int size2);
void *_realloc(void *old_ptr, unsigned int size1, unsigned int size2);
void _memcpy(void *to_ptr, const void *old_ptr, unsigned int ptr_size);

/* cd_funcs.c */
void cd_parent(cli_data *cli_frame);
void cd_dir(cli_data *cli_frame);
void cd_before(cli_data *cli_frame);
void cd_home_dir(cli_data *cli_frame);

/* check_funcs.c */
char *str_to_var(variables_t **head, char *str, char *str_new, int f_len);
char *str_var_func(char *str, cli_data *cli_frame);
void confirm_env(variables_t **head, char *str, cli_data *data);
int confirm_var(variables_t **hd, char *s, char *stat, cli_data *d);

/* cmd_funcs.c */
int check_curr(char *pp, int *idx);
char *find_cmd(char *command, char **_environ);
int check_exec(cli_data *cli_frame);
int verify_access(char *wd, cli_data *cli_frame);
int exec_cmd_line(cli_data *cli_frame);

/* cmd_line_funcs.c */
void assign_line(char **ptr_str, size_t *l, char *str, size_t b);
ssize_t read_input(char **ptr_str, size_t *l, FILE *p_strm);
int check_builtin(cli_data *cli_frame);
int (*find_builtn(char *cmmnd))(cli_data *cli_frame);
int rtrv_help_msg(cli_data *cli_frame);

/* cmd_split_funcs.c */
char *str_swp(char *str, int typ);
void add_to_list(separators_t **sep_h, command_lines_t **list_h, char *str);
void next_cmd(separators_t **sep_l, command_lines_t **llist, cli_data *cli_frame);
int sep_cmdl(cli_data *cli_frame, char *str);
char **str_to_toks(char *str);

/* env_funcs.c */
char *_getenv(const char *cmd_name, char **_environ);
int _env(cli_data *cli_frame);

/* env_funcs2.c */
int cmp_env(cli_data *cli_frame);
int rm_env(cli_data *cli_frame);
char *create_cpy(char *item, char *item_val);
void env_var_set(char *item, char *item_val, cli_data *cli_frame);

/* error_funcs.c */
char *cmd_not_found(cli_data *cli_frame);
char *cd_error(cli_data *cli_frame);
char *ccat_cd_err(cli_data *, char *, char *, char *);
char *exit_error(cli_data *cli_frame);

/* error_funcs2.c */
int call_error(cli_data *cli_frame, int err_v);
char *env_error(cli_data *cli_frame);
char *fail_error(cli_data *cli_frame);

/* help_funcs.c */
void bltn_env_help(void);
void cmp_env_help(void);
void rm_env_help(void);
void builtin_help(void);
void bltn_exit_help(void);

/* help_funcs2.c */
void help_info(void);
void cd_help_info(void);
void alias_help_info(void);

/* llists_funcs.c */
separators_t *append_sep(separators_t **hd, char sep);
void free_separators_t(separators_t **hd);
command_lines_t *append_cmdl(command_lines_t **hd, char *cmdl);
void free_command_lines_t(command_lines_t **hd);

/* llists_funcs2.c */
variables_t *append_var(variables_t **hd, int l1, char *s, int l2);
void free_vars_t(variables_t **hd);

/* loop_funcs.c */
char *rm_commnt(char *str);
void itr_cmd_l(cli_data *cli_frame);
int main_cd(cli_data *cli_frame);

/* shell_in_funcs.c */
char *read_in_str(int *last);
int main_exit(cli_data *cli_frame);
void hndl_ctrl_c(int signal);

/* stdlib_funcs.c */
int num_len(int n);
char *_to_string(int n);
int _atoi(char *c);
void str_revrse(char *str);

/* string_funcs.c */
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
int _strspn(char *s, char *a);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);

/* string_funcs2.c */
char *_strdup(const char *str);
int _isdigit(const char *s);
int _strlen(const char *s);
char *_strtok(char in[], const char *sep);
int str_compare(char in[], const char *sep);

/* syntax_funcs.c */
int char_count(char *str, int idx);
int find_sytx_err(char *str, int idx, char end);
int find_first_idx(char *str, int *idx);
int sytx_err_check(cli_data *cli_frame, char *str);
void sytx_err_print(cli_data *cli_frame, char *str, int idx, int check);

#endif

