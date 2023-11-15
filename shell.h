#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define NO_FILE_ERR
#define MEM_ALLOC_ERR
#define FORK_PROC_ERR
#define BUFF_CHUNKSIZE 1024
#define DELIMS


/**
* struct builtin_array - Array of builtin functions,
* @identity: name of builtin
* @function: pointer to function
*/

typedef struct builtin_array
{
	char *identity;
	int (*function)(void);
} builtin_array;



extern char **environ;

void tx_show_error(int err_code);
char *tx_strcat(char *target, char *origin);
char *tx_strdup(char *s);
int tx_strlen(char *s);
char **tx_split_string(char *str);
int tx_strncmp(char *str1, char *str2, unsigned int n);
char *tx_readline(FILE *file_input);
char *tx_strcpy(char *target, char *origin);
int tx_strcmp(char *source_str, char *comparison_str, unsigned int length);
int tx_exec_path(char *command_path, char **argv);
char *tx_search_direc(char *command, char *command_path, char *env_path);
char **tx_envcpy(char **target, char **origin, unsigned int size);
char *tx_getenv(const char *string);
int tx_builtin_exec(char **argv);
int tx_builtin_count(builtin_array options[]);
int tx_display_envc(void);
void tx_free_mem(char **argv, unsigned int number);
void tx_mem_dealloc(char **token_array, char *path_value, char *input_line,
char *command_path, int is_dynamic_path);

#endif /* SHELL_H */
