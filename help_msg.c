#include "shell.h"

/**
* get_help - This retrieve builtin help messages
* @infosh: represents data structure
* Return: returns null
*/
int get_help(shell_info *infosh)
{

if (infosh->arg_s[1] == 0)
display_general_help();
else if (_strcmp(infosh->arg_s[1], "setenv") == 0)
display_setenv_help();
else if (_strcmp(infosh->arg_s[1], "env") == 0)
display_env_help();
else if (_strcmp(infosh->arg_s[1], "unsetenv") == 0)
display_unsetenv_help();
else if (_strcmp(infosh->arg_s[1], "help") == 0)
display_help();
else if (_strcmp(infosh->arg_s[1], "exit") == 0)
display_exit_help();
else if (_strcmp(infosh->arg_s[1], "cd") == 0)
display_cd_help();
else if (_strcmp(infosh->arg_s[1], "alias") == 0)
display_help_alias();
else
write(STDERR_FILENO, infosh->arg_s[0],
_strlen(infosh->arg_s[0]));

infosh->status = 0;
return (1);
}
