#include "shell.h"

/**
* display_env_help - Display help information for the 'env' command.
* Return: void
*/
void display_env_help(void)
{
char *help_msg = "env: env [option] [name=value] [command [args]]\n\t";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "Display the TX shell's environment.\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
* display_setenv_help - Display help information for the
* 'setenv' command.
* Return: void
*/
void display_setenv_help(void)
{
char *help_msg =
"setenv: setenv (const char *name, const char *value, int replace)\n\t";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "Introduce a new definition to the environment.\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
* display_unsetenv_help - Display help information for the
* 'unsetenv' command.
* Return: void
*/
void display_unsetenv_help(void)
{
char *help_msg = "unsetenv: unsetenv (const char *name)\n\t";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "Completely remove an entry from the environment.\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
* display_general_help - Display general help information for the shell.
* Return: void
*/
void display_general_help(void)
{
char *help_msg = "TX$ bash, version 1.0(1)-release\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "These are internal commands. To view list, type 'help'.\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "To learn more about the 'id' function, type 'help id'.\n\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg =
"alias: alias [id=['string']]\n cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "exit: exit [n]\n env: env [option] [id=value] [command [args]]\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg =
"setenv: setenv [variable] [value]\n unsetenv: unsetenv [variable]\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
* display_exit_help - Display help information for the 'exit' command.
* Return: void
*/
void display_exit_help(void)
{
char *help_msg = "exit: exit [n]\n Exit TX shell.\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "Terminates the shell with a status of N. If N is not provided.\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "The exit status is that of the last executed command.\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}
