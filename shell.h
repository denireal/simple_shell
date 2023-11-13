#ifndef SHELL_H_INCLUDED
#define SHELL_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "helpers.h"

/* ======= Handling structures ======= */
/**
* struct info- struct for the program's information
* @progr_name: the name of the progr executable
* @input_line: pointer to the input read for tx_getline
* @the_cmd: pointer to the first command typed by the user
* @execution_ctr: number of excecuted comands
* @fd: file descriptor to the input of commands
* @token_arr: pointer to array of tokenized input
* @env_cpy: copy of the environ
* @alias_values: array of pointers with aliases.
*/
typedef struct shell_info
{
char *progr_name;
char *input_line;
char *the_cmd;
int execution_ctr;
int fd;
char **token_arr;
char **env_cpy;
char **alias_values;
} progr_info;

/**
* struct builtins - struct for the builtins
* @builtin: the name of the builtin
* @function: the associated function to be called for each builtin
*/
typedef struct builtins
{
char *builtin;
int (*function)(progr_info *info);
} builtins;

/* Read one line of the standar input*/
int tx_getline(progr_info *info);

/* split the each line for the logical operators if it exist */
int check_split_ops(char *cmd_input[], int cmd_index, char cmd_oper[]);

void var_exps(progr_info *info);

void alias_exps(progr_info *info);

int alias_append(char *unit_buff, char *str_copy);

void tx_tokenizer(progr_info *info);

char *_strtok(char *input_string, char *delimiters);

void tx_newline(int opr UNUSED);

void initialize_struct(progr_info *info, int argc, char *argv[], char **env);

void show_prompt(char *tx_prompt, progr_info *info);

int inspect_file(char *full_path);

int find_codepath(progr_info *info);

char **tokenize_path(progr_info *info);

int _imprimit(char *char_arr);

int error_inprimo(int code_err, progr_info *info);

void mem_dealloc_data(progr_info *info);

void dealloc_all_data(progr_info *info);

void mem_dealloc_array(char **array_ptr);

int execute(progr_info *info);

char *getenv_key(char *env_var, progr_info *info);

int setenv_key(char *env_var, char *value, progr_info *info);

int removeenv_key(char *env_var, progr_info *info);

void _imprimit_env(progr_info *info);

int search_exec_builtins(progr_info *info);

int exit_builtin(progr_info *info);

int cdir_builtin(progr_info *info);

int present_directory(progr_info *info, char *curr_dir);

int help_msg_builtin(progr_info *info);

int alias_builtin(progr_info *info);

int show_env(progr_info *info);

int setenv_var(progr_info *info);

int unsetenv_var(progr_info *info);

void long_string(long num, char *buff_string, int base_num);

int _atoi(char *str);

int count_characters(char *ptr_string, char *chars);

int str_length(char *s);

char *str_dup(char *s);

int str_compare(char *first_str, char *second_str, int number_char);

char *str_concat(char *first_str, char *second_str);

void str_reverse(char *s);

int write_alias(progr_info *info, char *alias_name);

char *fetch_alias(progr_info *info, char *alias_name);

int manage_alias(char *alias_string, progr_info *info);

#endif /* SHELL_H_INCLUDED */
