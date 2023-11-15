#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUFF_CHUNKSIZE 1024
#define DELIMS " \t\r\n\a"
#define FORK_PROC_ERR "Error in fork process\n"
#define MEM_ALLOC_ERR "Memory allocation error\n"
#define NO_FILE_ERR "File not found error\n"


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
unsigned int tx_strlen(const char *s);
char **tx_split_string(char *str);
unsigned int tx_strncmp(const char *str1, const char *str2, unsigned int n);
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
int tx_display_envc(void);
int tx_exit_shellc(void);

#endif /* SHELL_H */
