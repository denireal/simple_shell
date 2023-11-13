#include "shell.h"

/**
* var_exps - expansion of variables
* @info: a pointer to a struct of the program's info
*
* Return: void
*/
void var_exps(progr_info *info)
{
int i, j;
char unit[BUFFER_SIZE] = {0}, size[BUFFER_SIZE] = {'\0'}, *temp;

if (info->input_line == NULL)
return;

alias_append(unit, info->input_line);

for (i = 0; unit[i]; i++)
{
if (unit[i] == '#')
{
unit[i--] = '\0';
}
else if (unit[i] == '$' && unit[i + 1] == '?')
{
unit[i] = '\0';
long_string(errno, size, 10);
alias_append(unit, size);
alias_append(unit, info->input_line + i + 2);
}
else if (unit[i] == '$' && unit[i + 1] == '$')
{
unit[i] = '\0';
long_string(getpid(), size, 10);
alias_append(unit, size);
alias_append(unit, info->input_line + i + 2);
}
else if (unit[i] == '$' && (unit[i + 1] == ' ' || unit[i + 1] == '\0'))
{
continue;
}
else if (unit[i] == '$')
{
for (j = 1; unit[i + j] && unit[i + j] != ' '; j++)
{
size[j - 1] = unit[i + j];
}
size[j - 1] = '\0';
temp = getenv_key(size, info);
unit[i] = '\0';
size[0] = '\0';
alias_append(size, unit + i + j);
temp ? alias_append(unit, temp) : 1;
alias_append(unit, size);
}
}

if (!str_compare(info->input_line, unit, 0))
{
free(info->input_line);
info->input_line = str_dup(unit);
}
}

/**
* alias_exps - expansion of aliases
* @info: a pointer to a struct of the program's info
*
* Return: void
*/
void alias_exps(progr_info *info)
{
int i, j, exps_val = 0;
char unit[BUFFER_SIZE] = {0}, size[BUFFER_SIZE] = {'\0'}, *temp;

if (info->input_line == NULL)
return;

alias_append(unit, info->input_line);

for (i = 0; unit[i]; i++)
{
for (j = 0; unit[i + j] && unit[i + j] != ' '; j++)
{
size[j] = unit[i + j];
}
size[j] = '\0';

temp = fetch_alias(info, size);
if (temp)
{
size[0] = '\0';
alias_append(size, unit + i + j);
unit[i] = '\0';
alias_append(unit, temp);
alias_append(unit, size);
exps_val = 1;
}
break; /* Intended to break out of the loop after the first word */
}

if (exps_val)
{
free(info->input_line);
info->input_line = str_dup(unit);
}
}

/**
* alias_append - This append string at the end of the buffer
* @buffer: The buffer to be filled
* @unit_buff: string to be copied into the buffer
*
* Return: the new length of the buffer
*/
int alias_append(char *unit_buff, char *str_copy)
{
int length, i;

length = str_length(unit_buff);

for (i = 0; str_copy[i]; i++)
{
unit_buff[length + i] = str_copy[i];
}

unit_buff[length + i] = '\0';

return (length + i);
}
