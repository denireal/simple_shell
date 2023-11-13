#include "shell.h"
/**
* execute - This executes a command and its full path.
* @nfo: A pointer to the program's info.
* Return: Returns 0 on success; else returns -1.
*/
int execute(progr_info *info)
{
int result = 0, mode;
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
wait(&mode);
if (WIFEXITED(mode))
errno = WEXITSTATUS(mode);
else if (WIFSIGNALED(mode))
errno = 128 + WTERMSIG(mode);
}
}
return (0);
}
