#include "shell.h"

/**
* tx_builtin_exec - Executes the available built-in functions.
* @argv: A pointer to an array of strings.
* Return: An integer value representing the exit status.
*/
int tx_builtin_exec(char **argv)
{
int exit_status;
unsigned int command_length, num_builtins, index;

builtin_array options[] = {
{"exit", tx_exit_shellc},
{"env", tx_display_envc},
{NULL, NULL}
};

if (argv[0] == NULL)
return (1);

command_length = tx_strlen(argv[0]);

num_builtins = tx_builtin_count(options);
for (index = 0; index < num_builtins; index++)
{
if (tx_strcmp(argv[0], options[index].identity, command_length) == 0)
{
exit_status = (options[index].function)();
return (exit_status);
}
}
return (1);
}

/**
* tx_builtin_count - Counts the number of builtin functions available.
* @options: An array of built-ins.
* Return: The number of built-in functions.
*/
int tx_builtin_count(builtin_array options[])
{
unsigned int index = 0;

while (options[index].identity != NULL)
index++;

return (index);
}

/**
* tx_exit_shellc - Exits the shell.
* Return: An integer representing the exit status.
*/
int tx_exit_shellc(void)
{
return (-1);
}

/**
* tx_display_envc - Prints the environment variables.
* Return: An integer representing the exit status.
*/
int tx_display_envc(void)
{
unsigned int index = 0;
char **env = environ;

while (env[index] != NULL)
{
write(STDOUT_FILENO, env[index], tx_strlen(env[index]));
write(STDOUT_FILENO, "\n", 1);
index++;
}
return (0);
}
