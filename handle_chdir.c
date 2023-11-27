#include "shell.h"

/**
* _chdir - Changes current working directory based on user input.
* @datash: Pointer to the data structure containing shell information.
* Return: 1 on success, -1 on failure.
*/
int _chdir(shell_info *infosh)
{
char *target_dir;
int is_home, is_home_short, is_double_dash;

target_dir = infosh->arg_s[1];

if (target_dir != NULL)
{
is_home = _strcmp("$HOME", target_dir);
is_home_short = _strcmp("~", target_dir);
is_double_dash = _strcmp("--", target_dir);
}

if (target_dir == NULL || !is_home || !is_home_short || !is_double_dash)
{
cd_to_home(infosh);
return (1);
}

if (_strcmp("-", target_dir) == 0)
{
cd_previous(infosh);
return (1);
}

if (_strcmp(".", target_dir) == 0 || _strcmp("..", target_dir) == 0)
{
cd_dot(infosh);
return (1);
}

cd_to(infosh);

return (1);
}
