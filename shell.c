#include "shell.h"

/**
* free_alloc_mem - Frees allocated memory in the shell_info structure.
* @infosh: Pointer to the shell_info structure.
*/
void free_alloc_mem(shell_info *infosh)
{
unsigned int i;

for (i = 0; infosh->_envvar[i]; i++)
{
free(infosh->_envvar[i]);
}

free(infosh->_envvar);
free(infosh->pid);
}

/**
* init_shell - Initializes shell_info structure with data.
* @infosh: Pointer to the shell_info structure.
* @arg_v: Command-line arguments.
*/
void init_shell(shell_info *infosh, char **arg_v)
{
unsigned int i;

infosh->arg_v = arg_v;
infosh->input_line = NULL;
infosh->arg_s = NULL;
infosh->status = 0;
infosh->counter = 1;

/* Count the number of environment variables */
for (i = 0; environ[i]; i++)
;

/* Allocate memory for environment variables */
infosh->_envvar = malloc(sizeof(char *) * (i + 1));

/* Copy environment variables to infosh->_envvar */
for (i = 0; environ[i]; i++)
{
infosh->_envvar[i] = _strdup(environ[i]);
}

infosh->_envvar[i] = NULL; /* Terminate the array with NULL */
infosh->pid = int_to_str(getpid());
}

/**
* main - Entry point of the shell program.
* @arg_c: Number of command-line arguments.
* @arg_v: Array of command-line argument strings.
* Return: Exit status of the shell.
*/
int main(int arg_c, char **arg_v)
{
shell_info infosh;
(void)arg_c; /* Avoid unused variable warning */

signal(SIGINT, handle_interrupt_signal); /* Assuming get_sigint is defined somewhere */

init_shell(&infosh, arg_v);
exec_loop(&infosh); /* Assuming shell_loop is defined somewhere */

free_alloc_mem(&infosh);

if (infosh.status < 0)
return (255);

return (infosh.status);
}	
