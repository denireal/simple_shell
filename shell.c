#include "shell.h"

/**
* tx_prompt - checks for interactive mode and write prompt
* to standard output.
* Return: void
*/

void tx_prompt(void)
{
if (isatty(STDIN_FILENO))
{
write(STDOUT_FILENO, "TX-$ ", 5);
}
}

/**
* main - Entry point of the shell program.
* @argc: argument count.
* @argv: pointer to an array of strings.
* Return: 0 always
*/

int main(int argc, char **argv)
{
char *env_path, *full_path, *line_input;
int cmd_status, exec_status, flag = 0;
(void)argc;

env_path = full_path = line_input = NULL;
while (1)
{
tx_prompt();
line_input = tx_readline(stdin);
if (tx_strcmp(line_input, "\n", 1) == 0)
{	free(line_input);
continue;
}
argv = tx_split_string(line_input);
if (argv[0] == NULL)
continue;
cmd_status = tx_builtin_exec(argv);
if (cmd_status == 0 || cmd_status == -1)
{	free(argv);
free(line_input);
}
if (cmd_status == 0)
continue;
if (cmd_status == -1)
exit(0);
env_path = tx_getenv("PATH");
full_path = tx_search_direc(argv[0], full_path, env_path);
if (full_path == NULL)
{
full_path = argv[0];
}
else
flag = 1;

exec_status = tx_exec_path(full_path, argv);
if (exec_status == -1)
tx_show_error(2);
tx_mem_dealloc(argv, env_path, line_input, full_path, flag);
}
return (0);
}
