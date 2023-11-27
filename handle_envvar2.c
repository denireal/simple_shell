#include "shell.h"

/**
* copy_info - Create a new environment variable string
* @id: The identifier of the environment variable
* @value: The value of the environment variable
*
* Return: The newly created environment variable string
*/
char *copy_info(char *id, char *value)
{
int len_id, len_value, len;
char *new;

len_id = _strlen(id);
len_value = _strlen(value);
len = len_id + len_value + 2;
new = malloc(sizeof(char) * (len));
_strcpy(new, id);
_strcat(new, "=");
_strcat(new, value);
_strcat(new, "\0");

return (new);
}

/**
* set_env - Set or update an environment variable
* @id: The identifier of the environment variable
* @value: The value of the environment variable
* @infosh: The shell information
*/
void set_env(char *id, char *value, shell_info *infosh)
{
int i;
char *var_env, *name_env;

for (i = 0; infosh->_envvar[i]; i++)
{
var_env = _strdup(infosh->_envvar[i]);
name_env = _strtok(var_env, "="); if (_strcmp(name_env, id) == 0)
{
free(infosh->_envvar[i]);
infosh->_envvar[i] = copy_info(name_env, value);
free(var_env);
return;
}
free(var_env);
}

infosh->_envvar = _realloc_array(infosh->_envvar, i,
sizeof(char *) * (i + 2));
infosh->_envvar[i] = copy_info(id, value);
infosh->_envvar[i + 1] = NULL;
}

/**
* _setenv - Set or update an environment variable
* @infosh: The shell information
*
* Return: Always returns 1
*/
int _setenv(shell_info *infosh)
{
if (infosh->arg_s[1] == NULL || infosh->arg_s[2] == NULL)
{
get_error(infosh, -1);
return (1);
}

set_env(infosh->arg_s[1], infosh->arg_s[2], infosh);

return (1);
}

/**
* _unsetenv - Unset an environment variable
* @infosh: The shell information
*
* Return: Always returns 1
*/
int _unsetenv(shell_info *infosh)
{
char **_realloc_env;
char *var_env, *name_env;
int i, j, k;

if (infosh->arg_s[1] == NULL)
{
get_error(infosh, -1);
return (1);
}
k = -1;
for (i = 0; infosh->_envvar[i]; i++)
{
var_env = _strdup(infosh->_envvar[i]);
name_env = _strtok(var_env, "=");
if (_strcmp(name_env, infosh->arg_s[1]) == 0)
{
k = i;
}
free(var_env);
}
if (k == -1)
{
get_error(infosh, -1);
return (1);
}
_realloc_env = malloc(sizeof(char *) * (i));
for (i = j = 0; infosh->_envvar[i]; i++)
{
if (i != k)
{
_realloc_env[j] = infosh->_envvar[i];
j++;
}
}
_realloc_env[j] = NULL;
free(infosh->_envvar[k]);
free(infosh->_envvar);
infosh->_envvar = _realloc_env;
return (1);
}
