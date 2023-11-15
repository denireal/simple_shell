#include "shell.h"

/**
* tx_exec_path - Run a specified command using its complete path
* @command_path: A string indicating the full path
* @argv: A double pointer to a string containing the command
*        and its parameters
* Return: 0 upon success, -1 upon failure.
*/

int tx_exec_path(char *command_path, char **argv)
{
int status;
pid_t pid;

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}

if (pid == 0)
{
if (execve(command_path, argv, environ) == -1)
{
perror("execve");
exit(EXIT_FAILURE);
}
}
else
{
while (!WIFEXITED(status) && !WIFSIGNALED(status))
{
waitpid(pid, &status, 0);
}
}

return (0);
}

/**
* tx_search_direc - Explore directories in the PATH environment
* variable for a specified command.
* @command: The command to locate within the PATH directories.
* @command_path: Full path of the command for execution.
* @env_path: The value of the PATH environment variable.
* Return: Pointer to the full path or NULL if not found.
*/

char *tx_search_direc(char *command, char *command_path, char *env_path)
{
char *token_array;
struct stat file_stat;

if (!command || !env_path)
return (NULL);

env_path = strdup(env_path);
if (!env_path)
return (NULL);

for (token_array = strtok(env_path, ":"); token_array; token_array = strtok(NULL, ":"))
{
command_path = malloc(strlen(token_array) + strlen(command) + 2);
if (!command_path)
{
free(env_path);
return (NULL);
}

tx_strcpy(command_path, token_array);
tx_strcat(command_path, "/");
tx_strcat(command_path, command);

if (stat(command_path, &file_stat) == 0)
{
if ((file_stat.st_mode & S_IFMT) == S_IFREG && (file_stat.st_mode & S_IXUSR))
{
free(env_path);
return (command_path);
}
}

free(command_path);
}

free(env_path);
return (NULL);
}
