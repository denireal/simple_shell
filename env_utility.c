#include "shell.h"

/**
 * getenv_key - Retrieves the value of an environment variable.
 * @env_var: The environment variable of interest.
 * @info: The program's data structure.
 * Return: A pointer to the value of the variable or NULL if it doesn't exist.
 */
char *getenv_key(char *env_var, info *info)
{
int i, env_var_len = 0;

if (env_var == NULL || info->env == NULL)
return (NULL);

env_var_len = str_length(key);

for (i = 0; info->env[i]; i++)
{
if (str_compare(env_var, info->env_var[i], env_var_len) &&
info->env_var[i][env_var_len] == '=')
{
return (info->env_var[i] + env_var_len + 1);
}
}
return (NULL);
}

/**
 * setenv_key - Modifies the value of an environment variable,
 * creating it if it doesn't already exist.
 * @env_var: The name of the variable to be set.
 * @value: The new value.
 * @info: The program's data structure.
 * Return: 1 if the parameters are NULL, 2 if an error occurs,
 * or 0 if successful.
 */

int setenv_key(char *env_var, char *value, progr_info *info)
{
int i, env_var_len = 0, new_env_var = 1;

if (env_var == NULL || value == NULL || info->env_cpy == NULL)
return (1);

env_var_len = str_length(env_var);

for (i = 0; info->env_cpy[i]; i++)
{
if (str_compare(env_var, info->env_cpy[i], env_var_len) &&
info->env_cpy[i][env_var_len] == '=')
{

new_env_var = 0;

free(data->env_cpy[i]);
break;
}
}
info->env_cpy[i] = str_concat(str_dup(env_var), "=");
info->env_cpy[i] = str_concat(info->env_cpy[i], value);

if (new_env_var)
{
info->env_cpy[i + 1] = NULL;
}
return (0);
}

/**
 * removeenv_key - Deletes a key from the environment.
 * @env_var: The key to be deleted.
 * @info: The program's data structure.
 * Return: 1 if the key was successfully removed, 0 if the key does not exist.
 */
int removeenv_key(char *env_var, progr_info *info)
{
int i, env_var_len = 0;

if (env_var == NULL || info->env_cpy == NULL)
return (0);

env_var_len = str_length(env_var);

for (i = 0; info->env_cpy[i]; i++)
{
if (str_compare(env_var, info->env_cpy[i], env_var_len) &&
info->env_cpy[i][env_var_len] == '=')
{
free(info->env_cpy[i]);

i++;
for (; info->env_cpy[i]; i++)
{
info->env_cpy[i - 1] = info->env_cpy[i];
}

info->env_cpy[i - 1] = NULL;
return (1);
}
}
return (0);
}

/**
 * _imprimit_env - Prints the current environment.
 * @info: Struct for the program's information.
 * Return: void
 */
void _imprimit_env(progr_info *info)
{
int j;

for (j = 0; info->env_cpy[j]; j++)
{
_imprimit(info->env_cpy[j]);
_imprimit("\n");
}
}
