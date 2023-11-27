#include "shell.h"

/**
* exec_builtins - Execute built-in commands or external command
* @infosh: The shell information
*
* Return: 1 on success, 0 on failure
*/
int exec_builtins(shell_info *infosh)
{
int (*builtin)(shell_info *infosh);

if (infosh->arg_s[0] == NULL)
return (1);

builtin = get_builtin(infosh->arg_s[0]);

if (builtin != NULL)
return (builtin(infosh));

return (exec_cmdline(infosh));
}
