#include "shell.h"

/**
* get_error - THis gets the error regarding builtin, permission
* or syntax
* @infosh: represents the argument structure
* @error_val: The error value
* Return: error
*/
int get_error(shell_info *infosh, int error_val)
{
char *error;

switch (error_val)
{
case -1:
error = env_error_msg(infosh);
break;
case 126:
error = error_path(infosh);
break;
case 127:
error = command_not_found_error(infosh);
break;
case 2:
if (_strcmp("exit", infosh->arg_s[0]) == 0)
error = exit_shell_error(infosh);
else if (_strcmp("cd", infosh->arg_s[0]) == 0)
error = cd_error_message(infosh);
break;
}

if (error)
{
write(STDERR_FILENO, error, _strlen(error));
free(error);
}

infosh->status = error_val;
return (error_val);
}
