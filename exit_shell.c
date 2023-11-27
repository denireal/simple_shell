#include "shell.h"

/**
* exit_shell - Exits the shell with a specified status.
* @infosh: Relevant data (status and args).
*
* Return: 0 on success, 1 on failure.
*/
int exit_shell(shell_info *infosh)
{
unsigned int ustatus;
int status_code = 0;

if (infosh->arg_s[1] == NULL)
{
/* No argument provided, exit with default status (0) */
return (0);
}

ustatus = str_to_int(infosh->arg_s[1]);

if (!_isdigit(infosh->arg_s[1]) || _strlen(infosh->arg_s[1]) > 10 ||
ustatus > INT_MAX)
{
/* Invalid argument, print an error message */
get_error(infosh, 2);
infosh->status = 2;
status_code = 1;
}
else
{
/* Valid argument, set the exit status */
infosh->status = ustatus % 256;
}

return (status_code);
}
