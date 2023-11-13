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

/**
* var_exps - expansion of variables
* @info: a pointer to a struct of the program's info
*
* Return: void
*/
void var_exps(progr_info *info);

/**
* alias_exps - expansion of aliases
* @info: a pointer to a struct of the program's info
*
* Return: void
*/
void alias_exps(progr_info *info);

/**
* alias_append - This append string at the end of the buffer
* @buffer: The buffer to be filled
* @unit_buff: string to be copied into the buffer
*
* Return: the new length of the buffer
*/
int alias_append(char *unit_buff, char *str_copy);

/**
* tx_tokenizer - Separates the string into tokens using a designated delimiter
* @info: Pointer to the program's information
*/
void tx_tokenizer(progr_info *info);

/**
* _strtok - This separates strings using specified delimiters
* @input_string: Pointer to the array received from tx_getline
* @delimiters: Characters used as delimiters to split the string
*/
char *_strtok(char *input_string, char *delimiters);

/**
* tx_newline - Prints the prompt in a new line when sig is gotten
* @UNUSED: Placeholder for unused parameter in the prototype
*/
void tx_newline(int opr UNUSED);

/**
* initialize_struct - Initializes the program's info structure
* @info: Pointer to the structure holding program info
* @argv: Array of arguments passed to the program execution
* @env: Environment passed to the program execution
* @argc: Number of args received from the command line
*/
void initialize_struct(progr_info *info, int argc, char *argv[], char **env);

/**
* show_prompt - Displays the prompt in an infinite loop
* @tx_prompt: Prompt to be printed
* @info: Info relevant to the infinite loop
*/
void show_prompt(char *tx_prompt, progr_info *info);

/**
* inspect_file - Checks if a file exists, is not a directory,
* and has execution permissions.
* @full_path: Pointer to the full path name.
* Return: 0 on success, or an error code if it exists.
*/
int inspect_file(char *full_path);

/**
* find_codepath - Find a code path.
* @info: A pointer to the program's info.
* Return: 0 if success, error code otherwise.
*/
int find_codepath(progr_info *info);

/**
* tokenize_path - Tokenizes the path into directories.
* @info: A pointer to the program's info.
* Return: Array of path directories.
*/
char **tokenize_path(progr_info *info);

/**
* _imprimit - This prints an array of chars in the stdout
* @string: pointer to the array of chars
* Returns the count of written bytes or -1 on error,
* with the error code set in the errno variable.
*/
int _imprimit(char *char_arr);

/**
* error_inprimo - This prints an array of chars in the stderr
* @data: a pointer to the program's data'
* @code_err: error code to print
* Returns the count of written bytes or -1 on error,
* with the error code set in the errno variable.
*/
int error_inprimo(int code_err, progr_info *info);

/**
* mem_dealloc_data - This frees fields at each iteration.
* @info: A struct containing the program's info.
* Return: void.
*/
void mem_dealloc_data(progr_info *info);

/**
* dealloc_all_data - This free all field of the data
* @info: struct of the program's info
* Return: void
*/
void dealloc_all_data(progr_info *info);

/**
* mem_dealloc_array - this function frees each pointer of an array
* @array_ptr: An array of pointers
* Return: void
*/
void mem_dealloc_array(char **array_ptr);

/**
* execute - This executes a command and its full path.
* @nfo: A pointer to the program's info.
* Return: Returns 0 on success; else returns -1.
*/
int execute(progr_info *info);

/**
* getenv_key - Retrieves the value of an environment variable.
* @env_var: The environment variable of interest.
* @info: The program's data structure.
* Return: A pointer to the value of the variable or NULL if it doesn't exist.
*/
char *getenv_key(char *env_var, info *info);

/**
* setenv_key - Modifies the value of an environment variable,
* creating it if it doesn't already exist.
* @env_var: The name of the variable to be set.
* @value: The new value.
* @info: The program's data structure.
*/
int setenv_key(char *env_var, char *value, progr_info *info);

/**
* removeenv_key - Deletes a key from the environment.
* @env_var: The key to be deleted.
* @info: The program's data structure.
* Return: 1 if the key was successfully removed, 0 if the key does not exist.
*/
int removeenv_key(char *env_var, progr_info *info);

/**
* _imprimit_env - Prints the current environment.
* @info: Struct for the program's information.
* Return: void
*/
void _imprimit_env(progr_info *info);

/**
* search_exec_builtins - this search, match and execute builtin
* @info: struct for the program's info
* Return: Returns the function executed if there is a match,
* otherwise returns -1.
**/
int search_exec_builtins(progr_info *info);

/**
* exit_builtin - This exit the program with the particluar status.
* @info: Struct for the program's information.
* Return: 0 if success, or otherwise
*/
int exit_builtin(progr_info *info);

/**
* cdir_builtin - This changes the current directory.
* @info: Struct for the program's information.
* Return: 0 if success, or otherwise
*/
int cdir_builtin(progr_info *info);

/**
* present_directory - This set the present working directory.
* @info: Struct for the program's information.
* @new_dir: Path to be set as the working directory.
* Return: 0 if success, or otherwise
*/
int present_directory(progr_info *info, char *curr_dir);

/**
* help_msg_builtin - This displays help messages for builtin commands.
* @info: Struct for the program's information.
* Return: 0 if success, or otherwise
*/
int help_msg_builtin(progr_info *info);

/**
* alias_builtin - Add, remove, or show aliases.
* @info: Struct for the program's information.
* Return: 0 if success, or another
*/
int alias_builtin(progr_info *info);

/**
* show_env - Display the shell environment.
* @info: Struct for the program's information.
* Return: Zero if success, or another number
* if declared in the arguments.
*/
int show_env(progr_info *info);

/**
* setenv_var - Set an environment variable.
* @info: Struct for the program's information.
* Return: 0 if success, or another number
* if declared in the arguments.
*/
int setenv_var(progr_info *info);

/**
* unsetenv_var - Unset an environment variable.
* @info: Struct for the program's information.
* Return: Zero if success, or another number
* if declared in the arguments.
*/
int unsetenv_var(progr_info *info);

/**
* long_string - This converts a given number to a string.
* @num: number to be changed to a string.
* @buff_string: buffer to save the number as string.
* @base_num: base numbre to convert number
*/
void long_to_string(long num, char *buff_string, int base_num);

/**
* _atoi - This convert string to an integer.
*
* @str: pointer to str origin.
* Return: int of string or 0.
*/
int _atoi(char *str);

/**
* count_characters - This count character in a string.
* @ptr_string: pointer to the origin of the string.
* @chars: string with  chars to be counted
* Return: INT or 0.
*/
int count_characters(char *ptr_string, char *chars);

/**
* str_length - This prints the length of a string.
* @string: string.
* Return: length of string.
*/
int str_length(char *s);

/**
* str_dup - This duplicates a string
* @string: String
* Return: pointer to the array
*/
char *str_dup(char *s);

/**
* str_compare - This compare two or more strings
* @first_str: String one, or the shorter
* @second_str: String two, or the longer
* @number_char: number of characters to be compared
* Return: 1 if the strings are equals, 0 if the strings are not same
*/
int str_compare(char *first_str, char *second_str, int number_char);

/**
* str_concat - concatenates two or more strings.
* @first_str: First string to be concatenated
* @second_str: Second string to be concatenated
*
* Return: pointer to the array
*/
char *str_concat(char *first_str, char *second_str);

/**
* str_reverse - reverses a string.
*
* @string: pointer to string.
* Return: void.
*/
void str_reverse(char *s);

/**
* write_alias - Handles add, remove, or display aliases
* @info: struct for the program's information
* @alias_name: name of the alias to be displayed
* Return: 0 if success, or otherwise fail
*/
int write_alias(progr_info *info, char *alias_name);

/**
* fetch_alias - Handles adding, removing, or displaying aliases
* @info: struct for the program's information
* @alias_name: name of the requested alias.
* Return: 0 if success, or otherwise fail
*/
char *fetch_alias(progr_info *info, char *alias_name);

/**
* manage_alias - Handles adding or overriding aliases.
* @alias_string: Alias to be set in the form (name='value').
* @info: Struct for program information.
* Return: 0 if success, or otherwise fail
*/
int manage_alias(char *alias_string, progr_info *info);

#endif /* SHELL_H_INCLUD
