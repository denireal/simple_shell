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
        int exeution_ctr;
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



#endif /* SHELL_H_INCLUDED */
