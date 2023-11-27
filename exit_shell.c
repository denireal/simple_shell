#include "shell.h"

/**
* exit_shell - Handles the exit command in a shell program.
* @infosh: Pointer to the shell_info structure.
*
* Return: 0 on success, 1 on failure.
*/
int exit_shell(shell_info *infosh)
{
unsigned int ustatus;
int is_non_negative_integer;
int exit_status_str_len;
int exceeds_max_exit_status;

/* Check if an exit status argument is provided */
if (infosh->arg_s[1] != NULL)
{
/* Convert the argument to an integer */
ustatus = str_to_int(infosh->arg_s[1]);
/* Check if the argument is a non-negative integer */
is_non_negative_integer = _isnumber(infosh->arg_s[1]);
/* Get the length of the exit status string */
exit_status_str_len = _strlen(infosh->arg_s[1]);
/* Check if the exit status exceeds the maximum allowed value */
exceeds_max_exit_status = ustatus > MAX_EXIT_STATUS_VALUE;

/* Handle invalid exit status arguments */
if (!is_non_negative_integer || exit_status_str_len > MAX_EXIT_STATUS_LEN ||
exceeds_max_exit_status)
{
get_error(infosh, 2); /* Consider providing more detailed error messages */
infosh->status = 2;   /* Indicate an error status */
return (1);           /* Failure */
}

infosh->status = ustatus % (MAX_EXIT_STATUS_VALUE + 1);
}

return (0); /* Success */
}
