#include "shell.h"
/**
* execute - Runs a command with its full path variables.
* @data: A pointer to the program's data.
* Return: Returns zero on success; otherwise, returns -1.
*/
int execute(progr_info *info)
{
int result = 0, status;
pid_t pidd;

result =  search_exec_builtins(info);
if (result != -1)
return (result);

result = find_codepath(info);
if (result)
{
return (result);
}
else
{
pidd = fork();
if (pidd == -1)
{
perror(info->the_cmd);
exit(EXIT_FAILURE);
}
if (pidd == 0)
{
result = execve(info->token_arr[0], info->token_arr, info->env_cpy);
if (result == -1)
perror(info->the_cmd), exit(EXIT_FAILURE);
}
else
{
wait(&status);
if (WIFEXITED(status))
errno = WEXITSTATUS(status);
else if (WIFSIGNALED(status))
errno = 128 + WTERMSIG(status);
}
}
return (0);
}
