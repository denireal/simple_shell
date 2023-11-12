#include "shell.h"

/**
* show_env - Display the shell environment.
* @info: Struct for the program's information.
* Return: Zero if success, or another number
* if declared in the arguments.
*/
int show_env(progr_info *info)
{
int index;
char var_name[50] = {'\0'};
char *var_cpy = NULL;

if (info->token_arr[1] == NULL)
_imprimit_env(info);
else
{
for (index = 0; info->token_arr[1][index]; index++)
{
if (info->token_arr[1][index] == '=')
{
var_cpy = str_dup(getenv_key(var_name, info));
if (var_cpy != NULL)
setenv_key(var_name, info->token_arr[1] + index + 1, info);

_imprimit_env(info);
if (getenv_key(var_name, info) == NULL)
{
_imprimit(info->token_arr[1]);
_imprimit("\n");
}
else
{
setenv_key(var_name, var_cpy, info);
free(var_copy);
}
return (0);
}
var_name[index] = info->token_arr[1][index];
}
errno = 2;
perror(info->the_cmd);
errno = 127;
}
return (0);
}

/**
* setenv_var - Set an environment variable.
* @info: Struct for the program's information.
* Return: 0 if success, or another number
* if declared in the arguments.
*/
int setenv_var(progr_info *info)
{
if (info->token_arr[1] == NULL || info->token_arr[2] == NULL)
return (0);
if (info->token_arr[3] != NULL)
{
errno = E2BIG;
perror(info->the_cmd);
return (5);
}

setenv_key(info->token_arr[1], info->token_arr[2], info);

return (0);
}

/**
* unsetenv_var - Unset an environment variable.
* @info: Struct for the program's information.
* Return: Zero if success, or another number
* if declared in the arguments.
*/
int unsetenv_var(progr_info *info)
{
if (info->token_arr[1] == NULL)
return (0);
if (info->token_arr[2] != NULL)
{
errno = E2BIG;
perror(info->the_cmd);
return (5);
}

removeenv_key(info->token_arr[1], info);

return (0);
}
