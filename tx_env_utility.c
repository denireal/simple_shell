#include "shell.h"

/**
* tx_envcpy - Duplicates the environment variable array.
* @target: Pointer to the duplicated environment variable array.
* @origin: Pointer to the original environment variable array.
* @size: Size of the environment variable array.
* Return: Double pointer to the duplicated array.
*/
char **tx_envcpy(char **target, char **origin, unsigned int size)
{
char *current_var;
unsigned int current_var_size, index = 0;

target = malloc(sizeof(char *) * (size + 1));
if (target == NULL)
{
get_error(3);
return (NULL);
}

while (index < size)
{
current_var = origin[index];
current_var_size = _strlen(current_var);

target[index] = malloc(sizeof(char) * (current_var_size + 1));
if (target[index] == NULL)
{
get_error(3);
free_doubleP(target, index);
return NULL;
}

_strcpy(target[index], current_var);
index++;
}

target[index] = NULL;
return (target);
}

/**
* tx_getenv - Retrieves the value of a specific environment variable.
* @string: Pointer to a string representing the name of the target environment variable.
* Return: Value of the environment variable or NULL if not found.
*/
char *tx_getenv(const char *string)
{
int comparison_result;
char **env_copy = NULL;
char *value, *current_env, *current_value;
unsigned int value_size, env_size, string_size, index = 0;

env_size = 0;
while (environ[env_size] != NULL)
env_size++;

env_copy = tx_envcpy(env_copy, environ, env_size);

string_size = tx_strlen(string);
while (env_copy[index])
{
current_env = env_copy[index];
comparison_result = tx_strncmp(string, current_env, string_size);

if (comparison_result == 1)
{
current_value = strtok(current_env, "=");
current_value = strtok(NULL, "\n ");

if (current_value == NULL || *current_value == '\0')
{
tx_show_error(4);
exit(1);
}

value_size = tx_strlen(current_value);
value = malloc(sizeof(char) * (value_size + 1));

if (!value)
{
tx_show_error(3);
return (NULL);
}

tx_strcpy(value, current_value);
tx_free_mem(env_copy, env_size);
return (value);
}

index++;
}

return (NULL);
}
