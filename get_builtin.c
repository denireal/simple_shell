#include "shell.h"

/**
* get_builtin - Retrieve the function pointer for a built-in command.
* @command: The name of the command.
* Return: The function pointer for the specified built-in command.
*/
int (*get_builtin(char *command))(shell_info *)
{
t_builtin builtin[] = {
{"env", _env},
{"exit", exit_shell},
{"setenv", _setenv},
{"unsetenv", _unsetenv},
{"cd", _chdir},
{"help", get_help},
{NULL, NULL}
};

int i = 0;

while (builtin[i].id != NULL)
{
if (_strcmp(builtin[i].id, command) == 0)
return builtin[i].func;
i++;
}

return (NULL);
}
