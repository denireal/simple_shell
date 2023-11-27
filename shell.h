#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_EXIT_STATUS_LEN 10
#define MAX_EXIT_STATUS_VALUE 255

#define BUFF_CHUNKSIZE 1024
#define TOKEN_SIZE 128
#define DELIMITER " \t\r\n\a"

extern char **environ;

/**
* struct info - Structure to hold information about the shell.
* @arg_v: Array of strings representing command-line arguments.
* @input_line: Input line string.
* @arg_s: Array of strings representing tokenized input.
* @status: Status of the shell.
* @counter: Counter variable.
* @_envvar: Array of strings representing environment variables.
* @pid: Process ID string.
*/
typedef struct info
{
char **arg_v;
char *input_line;
char **arg_s;
int status;
int counter;
char **_envvar;
char *pid;
} shell_info;

/**
* struct s_list_sep - Structure for a linked list of separators.
* @separator: Separator character.
* @next_n: Pointer to the next node in the list.
*/
typedef struct s_list_sep
{
char separator;
struct s_list_sep *next_n;
} list_sep;

/**
* struct l_list_s - Structure for a linked list of lines.
* @line: Line string.
* @next_n: Pointer to the next node in the list.
*/
typedef struct l_list_s
{
char *line;
struct l_list_s *next_n;
} l_list;

/**
* struct s_list_var - Structure for a linked list of environment
* variables.
* @var_len: Length of the variable name.
* @val_var: Variable name string.
* @val_len: Length of the variable value.
* @next_n: Pointer to the next node in the list.
*/
typedef struct s_list_var
{
int var_len;
char *val_var;
int val_len;
struct s_list_var *next_n;
} list_var;

/**
* struct s_builtin - Structure for built-in commands.
* @id: Identifier for the built-in command.
* @func: Function pointer to the corresponding command function.
*/
typedef struct s_builtin
{
char *id;
int (*func)(shell_info *infosh);
} t_builtin;

void free_alloc_mem(shell_info *infosh);
void init_shell(shell_info *infosh, char **arg_v);
char *read_line(int *eof_stat);
char *remove_comment(char *input_string);
void exec_loop(shell_info *infosh);
char *swap_special_char(char *input_line, int is_reverse);
void add_separator_and_commands(list_sep **head_sep, l_list **head_list,
char *input_line);
void move_to_next(list_sep **l_sep, l_list **list_line, shell_info *infosh);
int split_command_exec(shell_info *infosh, char *input_line);
char **split_input(char *input_line);
void handle_interrupt_signal(int signal_num);
ssize_t get_line(char **line, size_t *line_size, FILE *stream);
void assign_line(char **line, size_t *line_size, char *buffer,
size_t buffer_size);
void display_exit_help(void);
void display_general_help(void);
void display_unsetenv_help(void);
void display_setenv_help(void);
void display_env_help(void);
void display_help(void);
void display_help_alias(void);
void display_cd_help(void);
char *concat_error_cd(shell_info *infosh, char *msg, char *error,
char *counter_str);
char *cd_error_message(shell_info *info);
char *command_not_found_error(shell_info *infosh);
char *exit_shell_error(shell_info *infosh);
char *env_error_msg(shell_info *infosh);
char *error_path(shell_info *infosh);
void free_line_list(l_list **head);
l_list *line_node_point(l_list **head, char *line);
void free_sep_list(list_sep **head);
list_sep *sep_node_point(list_sep **head, char sep);
void free_variable_list(list_var **head);
list_var *add_variable_node(list_var **head, int var_length, char *value,
int value_length);
char **_realloc_array(char **arr, unsigned int old_size,
unsigned int new_size);
void *_realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size);
void _memcpy(void *dest, const void *src, unsigned int size);
int str_to_int(char *str);
char *int_to_str(int number);
int get_len(int number);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *str1, char *str2);
char *_strchr(char *str, char xter);
int _strspn(char *str, char *accept);
int _isnumber(const char *str);
char *_strtok(char str[], const char *delim);
int cmp_chars(char str[], const char *delim);
int _strlen(const char *str);
char *_strdup(const char *str);
void rev_string(char *s);
void cd_dot(shell_info *infosh);
void cd_to(shell_info *infosh);
void cd_previous(shell_info *infosh);
void cd_to_home(shell_info *infosh);
int repetition_char(char *input, int i);
int sep_op_error(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(shell_info *infosh, char *input, int i, int bool);
int _syntax_error(shell_info *infosh, char *input_line);
int if_char_colon(char *p, int *index);
char *_locate(char *command, char **_envvar);
int if_executable(shell_info *infosh);
int check_permission(char *dir, shell_info *infosh);
int exec_cmdline(shell_info *infosh);
int cmp_env_id(const char *_envvar, const char *id);
char *_getenv(const char *id, char **_envvar);
int _env(shell_info *infosh);
char *copy_info(char *id, char *value);
void set_env(char *id, char *value, shell_info *infosh);
int _setenv(shell_info *infosh);
int _unsetenv(shell_info *infosh);
int exec_builtins(shell_info *infosh);
int exit_shell(shell_info *infosh);
int get_error(shell_info *infosh, int error_val);
int get_help(shell_info *infosh);
char *replace_variables(char *input, shell_info *infosh);
char *replaced_input(list_var **list_var_head, char *input, char *new_input,
int new_len);
int check_vars(list_var **h, char *in, char *st, shell_info *info);
void check_env(list_var **h, char *in, shell_info *info);
int (*get_builtin(char *command))(shell_info *);
int _chdir(shell_info *infosh);

#endif /* _SHELL_H */
