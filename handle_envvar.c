#include "shell.h"

/**
* cmp_env_id - Compare the identifier part of an environment variable
* @_envvar: The environment variable
* @id: The identifier to compare
*
* Return: The length of the matching identifier, 0 if not found
*/
int cmp_env_id(const char *_envvar, const char *id)
{
int length;

for (length = 0; _envvar[length] != '='; length++)
{
if (_envvar[length] != id[length])
{
return (0);
}
}

return (length + 1);
}

/**
* _getenv - Get the value of an environment variable
* @id: The identifier of the environment variable
* @_envvar: The array of environment variables
*
* Return: The value of the environment variable, NULL if not found
*/
char *_getenv(const char *id, char **_envvar)
{
char *env_ptr;
int offset, i;

env_ptr = NULL;
offset = 0;

for (i = 0; _envvar[i]; i++)
{
offset = cmp_env_id(_envvar[i], id);
if (offset)
{
env_ptr = _envvar[i];
break;
}
}

return (env_ptr + offset);
}

/**
* _env - Print all environment variables
* @infosh: The shell information
*
* Return: Always returns 1
*/
int _env(shell_info *infosh)
{
int length, i;

for (i = 0; infosh->_envvar[i]; i++)
{
for (length = 0; infosh->_envvar[i][length]; length++)
;

write(STDOUT_FILENO, infosh->_envvar[i], length);
write(STDOUT_FILENO, "\n", 1);
}
infosh->status = 0;

return (1);
}
