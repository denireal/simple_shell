#include "shell.h"

/**
* inspect_file - Checks if a file exists, is not a directory,
* and has execution permissions.
* @full_path: Pointer to the full path name.
* Return: 0 on success, or an error code if it exists.
*/
int inspect_file(char *full_path)
{
struct stat file_stat;

if (stat(full_path, &file_stat) != -1)
{
if (S_ISDIR(file_stat.st_mode) || access(full_path, X_OK))
{
errno = 126;
return 126;
}
return 0;
}
errno = 127;
return 127;
}

/**
* find_codepath - Find a code path.
* @info: A pointer to the program's info.
* Return: 0 if success, error code otherwise.
*/
int find_codepath(progr_info *info)
{
int i;
int code_val = 0;
char **progr_dirs;

if (!info->program_name)
return 2;

if (info->program_name[0] == '/' || info->program_name[0] == '.')
return inspect_file(info->program_name);

free(info->token_arr[0]);
info->token_arr[0] = str_concat(str_dup("/"), info->program_name);
if (!info->token_arr[0])
return 2;

progr_dirs = tokenize_path(info);

if (!progr_dirs || !progr_dirs[0])
{
errno = 127;
return 127;
}

for (i = 0; progr_dirs[i]; i++)
{
progr_dirs[i] = str_concat(progr_dirs[i], info->token_arr[0]);
code_val = inspect_file(progr_dirs[i]);
if (code_val == 0 || code_val == 126)
{
errno = 0;
free(info->token_arr[0]);
info->token_arr[0] = str_dup(progr_dirs[i]);
mem_dealloc_array(progr_dirs);
return code_val;
}
}

free(info->token_arr[0]);
info->token_arr[0] = NULL;
mem_dealloc_array(progr_dirs);
return code_val;
}

/**
* tokenize_path - Tokenizes the path into directories.
* @info: A pointer to the program's info.
* Return: Array of path directories.
*/
char **tokenize_path(progr_info *info)
{
int counter_dirs = 2;
int i = 0;
char *path;
char **token_arr = NULL;

path = getenv_key("PATH", info);
if (!path || path[0] == '\0')
return NULL;

path = str_dup(path);

for (i = 0; path[i]; i++)
{
if (path[i] == ':')
counter_dirs++;
}

token_arr = malloc(sizeof(char *) * counter_dirs);

i = 0;
token_arr[i] = str_dup(_strtok(path, ":"));
while (token_arr[i])
{
i++;
token_arr[i] = str_dup(_strtok(NULL, ":"));
}

free(path);
path = NULL;
return (token_arr);
}
