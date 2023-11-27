#include "shell.h"

/**
* if_char_colon - Check if the character is a colon
* @p: The string
* @index: The current index in the string
*
* Return: 1 if the character is a colon, 0 otherwise
*/
int if_char_colon(char *p, int *index)
{
if (p[*index] == ':')
return (1);

while (p[*index] != ':' && p[*index])
{
(*index)++;
}

if (p[*index])
(*index)++;

return (0);
}

/**
* _locate - Locate the executable in the PATH
* @command: The command to locate
* @_envvar: The environment variables
*
* Return: The path to the executable or NULL if not found
*/
char *_locate(char *command, char **_envvar)
{
char *path, *path_copy, *token, *directory;
int len_directory, len_command, index;
struct stat st;

path = _getenv("PATH", _envvar);
if (path)
{
path_copy = _strdup(path);
len_command = _strlen(command);
token = _strtok(path_copy, ":");
index = 0;
while (token != NULL)
{
if (if_char_colon(path, &index))
if (stat(command, &st) == 0)
return (command);
len_directory = _strlen(token);
directory = malloc(len_directory + len_command + 2);
_strcpy(directory, token);
_strcat(directory, "/");
_strcat(directory, command);
_strcat(directory, "\0");
if (stat(directory, &st) == 0)
{
free(path_copy);
return (directory);
}
free(directory);
token = _strtok(NULL, ":");
}
free(path_copy);
if (stat(command, &st) == 0)
return (command);
return (NULL);
}
if (command[0] == '/')
if (stat(command, &st) == 0)
return (command);
return (NULL);
}

/**
* if_executable - Check if the input is an executable
* @infosh: The shell information
*
* Return: Length of the input string if it's an executable, -1 otherwise
*/
int if_executable(shell_info *infosh)
{
struct stat st;
int i;
char *input;

input = infosh->arg_s[0];
for (i = 0; input[i]; i++)
{
if (input[i] == '.')
{
if (input[i + 1] == '.')
return (0);
if (input[i + 1] == '/')
continue;
else
break;
}
else if (input[i] == '/' && i != 0)
{
if (input[i + 1] == '.')
continue;
i++;
break;
}
else
break;
}
if (i == 0)
return (0);

if (stat(input + i, &st) == 0)
return (i);

get_error(infosh, 127);
return (-1);
}

/**
* check_permission - Check if the shell has permission to execute
* @dir: The directory path
* @infosh: The shell information
*
* Return: 1 if permission denied, 0 otherwise
*/
int check_permission(char *dir, shell_info *infosh)
{
if (dir == NULL)
{
get_error(infosh, 127);
return (1);
}

if (_strcmp(infosh->arg_s[0], dir) != 0)
{
if (access(dir, X_OK) == -1)
{
get_error(infosh, 126);
free(dir);
return (1);
}
free(dir);
}
else
{
if (access(infosh->arg_s[0], X_OK) == -1)
{
get_error(infosh, 126);
return (1);
}
}

return (0);
}

/**
* exec_cmdline - Execute the shell command line
* @infosh: The shell information
*
* Return: 1 on success, 0 on failure
*/
int exec_cmdline(shell_info *infosh)
{
pid_t pid, wpid;
int state;
int exec;
char *dir;
(void)wpid;

exec = if_executable(infosh);
if (exec == -1)
return (1);
if (exec == 0)
{
dir = _locate(infosh->arg_s[0], infosh->_envvar);
if (check_permission(dir, infosh) == 1)
return (1);
}

pid = fork();
if (pid == 0)
{
if (exec == 0)
dir = _locate(infosh->arg_s[0], infosh->_envvar);
else
dir = infosh->arg_s[0];
execve(dir + exec, infosh->arg_s, infosh->_envvar);
}
else if (pid < 0)
{
perror(infosh->arg_v[0]);
return (1);
}
else
{
do
{
wpid = waitpid(pid, &state, WUNTRACED);
} while (!WIFEXITED(state) && !WIFSIGNALED(state));
}

infosh->status = state / 256;
return (1);
}
