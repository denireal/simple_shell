#include "shell.h"

/**
* display_help - Display information about builtin commands.
*
* Return: void
*/
void display_help(void)
{
char *help_msg = "help: help [-dms] [pattern ...]\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "\tDisplay builtin command info.\n ";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "Displays builtin commands summary.\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
* display_alias_help - Define or display aliases.
*
* Return: void
*/
void display_help_alias(void)
{
char *help_msg = "alias: alias [-p] [name[=value]...]\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "\tDisplay the aliases.\n ";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
* display_cd_help - Change the shell working directory.
*
* Return: void
*/
void display_cd_help(void)
{
char *help_msg = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));

help_msg = "\tChange the TX shell working directory.\n ";
write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}
