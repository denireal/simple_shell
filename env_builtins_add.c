#include "shell.h"

/**
* exit_builtin - This exit the program with the particluar status.
* @info: Struct for the program's information.
* Return: 0 if success, or otherwise
*/
int exit_builtin(progr_info *info)
{
int ind;

if (info->token_arr[1] != NULL)
{

for (ind = 0; info->token_arr[1][ind]; ind++)
if ((info->token_arr[1][ind] < '0' || info->token_arr[1][ind] > '9') && info->token_arr[1][ind] != '+')
{

errno = 2;
return (2);
}
errno = _atoi(info->token_arr[1]);
}
dealloc_all_data(info);
exit(errno);
}

/**
* cdir_builtin - This changes the current directory.
* @info: Struct for the program's information.
* Return: 0 if success, or otherwise
*/
int cdir_builtin(progr_info *info)
{
char *home_dir = getenv_key("HOME", info), *O_dir = NULL;
char prev_dir[128] = {0};
int error_code = 0;

if (info->token_arr[1])
{
if (str_compare(info->token_arr[1], "-", 0))
{
O_dir = getenv_key("OLDPWD", info);
if (O_dir)
error_code = present_directory(info, O_dir);
_imprimit(getenv_key("PWD", info));
_imprimit("\n");

return (error_code);
}
else
{
return (present_directory(info, info->token_arr[1]));
}
}
else
{
if (!home_dir)
home_dir = getcwd(prev_dir, 128);

return (present_directory(info, home_dir));
}
return (0);
}

/**
* present_directory - This set the present working directory.
* @info: Struct for the program's information.
* @new_dir: Path to be set as the working directory.
* Return: 0 if success, or otherwise
*/
int present_directory(progr_info *info, char *curr_dir)
{
char prev_dir[128] = {0};
int err_code = 0;

getcwd(prev_dir, 128);

if (!str_compare(prev_dir, curr_dir, 0))
{
err_code = chdir(curr_dir);
if (err_code == -1)
{
errno = 2;
return (3);
}
setenv_key("PWD", curr_dir, info);
}
setenv_key("OLDPWD", prev_dir, info);
return (0);
}

/**
* help_msg_builtin - This displays help messages for builtin commands.
* @info: Struct for the program's information.
* Return: 0 if success, or otherwise 
*/
int help_msg_builtin(progr_info *info)
{
int ind, length = 0;
char *nuntius[6] = {NULL}; /* nuntius is latin for message */

nuntius[0] = HELP_MSG;

if (info->token_arr[1] == NULL)
{
_imprimit(nuntius[0] + 6);
return (1);
}
if (info->token_arr[2] != NULL)
{
errno = E2BIG;
perror(info->progr_name);
return (5);
}
nuntius[1] = HELP_EXIT_MSG;
nuntius[2] = HELP_ENV_MSG;
nuntius[3] = HELP_SETENV_MSG;
nuntius[4] = HELP_UNSETENV_MSG;
nuntius[5] = HELP_CD_MSG;

for (ind = 0; nuntius[ind]; ind++)
{
length = str_length(info->token_arr[1]);
if (str_compare(info->token_arr[1], nuntius[ind], length))
{
_imprimit(nuntius[ind] + length + 1);
return (1);
}
}
errno = EINVAL;
perror(info->progr_name);
return (0);
}

/**
* alias_builtin - Add, remove, or show aliases.
* @info: Struct for the program's information.
* Return: 0 if success, or another 
*/
int alias_builtin(progr_info *info)
{
int ind = 0;

if (info->token_arr[1] == NULL)
return (write_alias(info, NULL));

while (info->token_arr[++ind])
{
if (count_characters(info->token_arr[ind], "="))
manage_alias(info->token_arr[ind], info);
else
write_alias(info, info->token_arr[ind]);
}

return (0);
}
