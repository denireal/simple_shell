#include "shell.h"

/**
* env_error_msg - Generates an error message for environment-related
* commands.
* @infosh: Shell information structure containing relevant information
* (counter, arguments).
*
* Return: Error message.
*/
char *env_error_msg(shell_info *infosh)
{
int length;
char *error;
char *ver_str;
char *msg;

ver_str = int_to_str(infosh->counter);
msg = ": Cannot add or remove from environment\n";
length = _strlen(infosh->arg_v[0]) + _strlen(ver_str);
length += _strlen(infosh->arg_s[0]) + _strlen(msg) + 4;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}

_strcpy(error, infosh->arg_v[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, infosh->arg_s[0]);
_strcat(error, msg);
_strcat(error, "\0");
free(ver_str);

return (error);
}

/**
* error_path - Generates an error message for permission failure.
* @infosh: Shell information structure containing relevant information
* (counter, arguments).
*
* Return: Error message.
*/
char *error_path(shell_info *infosh)
{
int length;
char *ver_str;
char *error;

ver_str = int_to_str(infosh->counter);
length = _strlen(infosh->arg_v[0]) + _strlen(ver_str);
length += _strlen(infosh->arg_s[0]) + 24;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}
_strcpy(error, infosh->arg_v[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, infosh->arg_s[0]);
_strcat(error, ": Permission failed\n");
_strcat(error, "\0");
free(ver_str);

return (error);
}
