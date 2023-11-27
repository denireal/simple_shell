#include "shell.h"

/**
* concat_error_cd - Concatenates the error message for the 'cd' command.
* @infosh: Shell information structure containing relevant information
* (directory).
* @msg: Message to print.
* @error: Output message buffer.
* @counter_str: Counter lines.
*
* Return: Error message.
*/
char *concat_error_cd(shell_info *infosh, char *msg, char *error,
char *counter_str)
{
char *flag;

_strcpy(error, infosh->arg_v[0]);
_strcat(error, ": ");
_strcat(error, counter_str);
_strcat(error, ": ");
_strcat(error, infosh->arg_s[0]);
_strcat(error, msg);

if (infosh->arg_s[1][0] == '-')
{
flag = malloc(3);
flag[0] = '-';
flag[1] = infosh->arg_s[1][1];
flag[2] = '\0';
_strcat(error, flag);
free(flag);
}
else
{
_strcat(error, infosh->arg_s[1]);
}

_strcat(error, "\n");
_strcat(error, "\0");
return (error);
}

/**
* cd_error_message - Generates an error message for 'cd' command
* @infosh: Shell information structure containing relevant information
* (directory).
*
* Return: Error message.
*/
char *cd_error_message(shell_info *infosh)
{
int length, id_len;
char *error, *counter_str, *msg;

counter_str = int_to_str(infosh->counter);
if (infosh->arg_s[1][0] == '-')
{
msg = ": Invalid option ";
id_len = 2;
}
else
{
msg = ": unable to cd ";
id_len = _strlen(infosh->arg_s[1]);
}

length = _strlen(infosh->arg_v[0]) + _strlen(infosh->arg_s[0]);
length += _strlen(counter_str) + _strlen(msg) + id_len + 5;
error = malloc(sizeof(char) * (length + 1));

if (error == 0)
{
free(counter_str);
return (NULL);
}

error = concat_error_cd(infosh, msg, error, counter_str);

free(counter_str);

return (error);
}

/**
* command_not_found_error - Generates a generic error message
* for command not found.
* @infosh: Shell information structure containing relevant information
* (counter, arguments).
*
* Return: Error message.
*/
char *command_not_found_error(shell_info *infosh)
{
int length;
char *error;
char *counter_str;

counter_str = int_to_str(infosh->counter);
length = _strlen(infosh->arg_v[0]) + _strlen(counter_str);
length += _strlen(infosh->arg_s[0]) + 16;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(error);
free(counter_str);
return (NULL);
}
_strcpy(error, infosh->arg_v[0]);
_strcat(error, ": ");
_strcat(error, counter_str);
_strcat(error, ": ");
_strcat(error, infosh->arg_s[0]);
_strcat(error, ": not available\n");
_strcat(error, "\0");
free(counter_str);

return (error);
}

/**
* exit_shell_error - Generates a generic error message for 'exit'
* @infosh: Shell information structure containing relevant information
* (counter, arguments).
*
* Return: Error message.
*/
char *exit_shell_error(shell_info *infosh)
{
int length;
char *error;
char *counter_str;

counter_str = int_to_str(infosh->counter);
length = _strlen(infosh->arg_v[0]) + _strlen(counter_str);
length += _strlen(infosh->arg_s[0]) + _strlen(infosh->arg_s[1]) + 23;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(counter_str);
return (NULL);
}
_strcpy(error, infosh->arg_v[0]);
_strcat(error, ": ");
_strcat(error, counter_str);
_strcat(error, ": ");
_strcat(error, infosh->arg_s[0]);
_strcat(error, ": Invalid number: ");
_strcat(error, infosh->arg_s[1]);
_strcat(error, "\n\0");
free(counter_str);

return (error);
}
