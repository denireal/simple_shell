#include "shell.h"

/**
* search_exec_builtins - this search, match and execute builtin
* @info: struct for the program's info
* Return: Returns the function executed if there is a match,
* otherwise returns -1.
**/
int search_exec_builtins(progr_info *info)
{
int i;

builtins options[] = {
{"exit", exit_builtin},
{"help", help_msg_builtin},
{"cd", cdir_builtin},
{"alias", alias_builtin},
{"env_cpy", show_env},
{"setenv", setenv_var},
{"unsetenv", unsetenv_var},
{NULL, NULL}
};

for (i = 0; options[i].builtin != NULL; i++)
{
if (str_compare(options[i].builtin, info->the_cmd, 0))
{

return (options[i].function(info));
}
}
return (-1);
}
