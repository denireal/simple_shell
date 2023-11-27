#include "shell.h"

/**
* remove_comment - Remove comments from the input string.
* @input_string: Input string.
*
* Return: Modified string without comments or NULL if the entire
* line is a comment.
*/
char *remove_comment(char *input_string)
{
int i, comment_end;

comment_end = 0;
for (i = 0; input_string[i]; i++)
{
if (input_string[i] == '#')
{
if (i == 0)
{
free(input_string);
return (NULL);
}

if (input_string[i - 1] == ' ' || input_string[i - 1] == '\t' ||
input_string[i - 1] == ';')
comment_end = i;
}
}

if (comment_end != 0)
{
input_string = _realloc_mem(input_string, i, comment_end + 1);
input_string[comment_end] = '\0';
}

return (input_string);
}

/**
* exec_loop - Main loop of the shell program.
* @infosh: Pointer to the shell_info structure.
*/
void exec_loop(shell_info *infosh)
{
int loop, eof_stat;
char *input_line;

loop = 1;
while (loop == 1)
{
write(STDIN_FILENO, "^-^ ", 4);
input_line = read_line(&eof_stat);
if (eof_stat != -1)
{
input_line = remove_comment(input_line);
if (input_line == NULL)
continue;

if (_syntax_error(infosh, input_line) == 1)
{
infosh->status = 2;
free(input_line);
continue;
}
input_line = replace_variables(input_line, infosh);
loop = split_command_exec(infosh, input_line);
infosh->counter += 1;
free(input_line);
}
else
{
loop = 0;
free(input_line);
}
}
}
