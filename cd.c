#include "shell.h"

/**
* cd_dot - Change directory to the given path or stay in the
* current directory.
* @infosh: Pointer to the shell_info struct.
*/
void cd_dot(shell_info *infosh)
{
char current_path[PATH_MAX];
char *directory, *copy_pwd, *token_pwd;

getcwd(current_path, sizeof(current_path));
copy_pwd = _strdup(current_path);
set_env("OLDPWD", copy_pwd, infosh);
directory = infosh->arg_s[1];

if (_strcmp(".", directory) == 0)
{
set_env("PWD", copy_pwd, infosh);
free(copy_pwd);
return;
}

if (_strcmp("/", copy_pwd) == 0)
{
free(copy_pwd);
return;
}

token_pwd = copy_pwd;
rev_string(token_pwd);
token_pwd = _strtok(token_pwd, "/");

if (token_pwd != NULL)
{
token_pwd = _strtok(NULL, "\0");

if (token_pwd != NULL)
rev_string(token_pwd);
}

if (token_pwd != NULL)
{
chdir(token_pwd);
set_env("PWD", token_pwd, infosh);
}
else
{
chdir("/");
set_env("PWD", "/", infosh);
}

infosh->status = 0;
free(copy_pwd);
}

/**
* cd_to - Change directory to the specified path.
* @infosh: Pointer to the shell_info struct.
*/
void cd_to(shell_info *infosh)
{
char current_path[PATH_MAX];
char *directory, *copy_pwd, *copy_directory;

getcwd(current_path, sizeof(current_path));
directory = infosh->arg_s[1];

if (chdir(directory) == -1)
{
get_error(infosh, 2);
return;
}

copy_pwd = _strdup(current_path);
set_env("OLDPWD", copy_pwd, infosh);

copy_directory = _strdup(directory);
set_env("PWD", copy_directory, infosh);

free(copy_pwd);
free(copy_directory);

infosh->status = 0;

chdir(directory);
}

/**
* cd_previous - Change directory to the previous directory.
* @infosh: Pointer to the shell_info struct.
*/
void cd_previous(shell_info *infosh)
{
char current_path[PATH_MAX];
char *previous_pwd, *old_pwd, *copy_pwd, *copy_old_pwd;

getcwd(current_path, sizeof(current_path));
copy_pwd = _strdup(current_path);

old_pwd = _getenv("OLDPWD", infosh->_envvar);

if (old_pwd == NULL)
copy_old_pwd = copy_pwd;
else
copy_old_pwd = _strdup(old_pwd);

set_env("OLDPWD", copy_pwd, infosh);

if (chdir(copy_old_pwd) == -1)
set_env("PWD", copy_pwd, infosh);
else
set_env("PWD", copy_old_pwd, infosh);

previous_pwd = _getenv("PWD", infosh->_envvar);

write(STDOUT_FILENO, previous_pwd, _strlen(previous_pwd));
write(STDOUT_FILENO, "\n", 1);

free(copy_pwd);
if (old_pwd)
free(copy_old_pwd);

infosh->status = 0;

chdir(previous_pwd);
}

/**
* cd_to_home - Change directory to the user's home directory.
* @infosh: Pointer to the shell_info struct.
*/
void cd_to_home(shell_info *infosh)
{
char *previous_pwd, *home;
char current_path[PATH_MAX];

getcwd(current_path, sizeof(current_path));
previous_pwd = _strdup(current_path);

home = _getenv("HOME", infosh->_envvar);

if (home == NULL)
{
set_env("OLDPWD", previous_pwd, infosh);
free(previous_pwd);
return;
}

if (chdir(home) == -1)
{
get_error(infosh, 2);
free(previous_pwd);
return;
}

set_env("OLDPWD", previous_pwd, infosh);
set_env("PWD", home, infosh);
free(previous_pwd);
infosh->status = 0;
}
