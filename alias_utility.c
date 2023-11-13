#include "shell.h"

/**
* write_alias - Handles add, remove, or display aliases
* @info: struct for the program's information
* @alias_name: name of the alias to be displayed
* Return: 0 if success, or otherwise fail
*/
int write_alias(progr_info *info, char *alias_name)
{
int index, char_index, alias_length;
char buffer[250] = {'\0'};

if (info->alias_values)
{
alias_length = str_length(alias_name);
for (index = 0; info->alias_values[index]; index++)
{
if (!alias_name || (str_compare(info->alias_values[index], alias_name, alias_length)
&&	info->alias_values[index][alias_length] == '='))
{
for (char_index = 0; info->alias_values[index][char_index]; char_index++)
{
buffer[char_index] = info->alias_values[index][char_index];
if (info->alias_values[index][char_index] == '=')
break;
}
buffer[char_index + 1] = '\0';
alias_append(buffer, "'");
alias_append(buffer, info->alias_values[index] + char_index + 1);
alias_append(buffer, "'\n");
_imprimit(buffer);
}
}
}

return (0);
}

/**
* fetch_alias - Handles adding, removing, or displaying aliases
* @info: struct for the program's information
* @alias_name: name of the requested alias.
* Return: 0 if success, or otherwise fail
*/
char *fetch_alias(progr_info *info, char *alias_name)
{
int index, alias_length;


if (alias_name == NULL || info->alias_values == NULL)
return (NULL);

alias_length = str_length(alias_name);

for (index = 0; info->alias_values[index]; index++)
{
if (str_compare(alias_name, info->alias_values[index], alias_length) &&
info->alias_values[index][alias_length] == '=')
{

return (info->alias_values[index] + alias_length + 1);
}
}

return (NULL);
}

/**
* manage_alias - Handles adding or overriding aliases.
* @alias_string: Alias to be set in the form (name='value').
* @info: Struct for program information.
* Return: 0 if success, or otherwise fail
*/
int manage_alias(char *alias_string, progr_info *info)
{
int ind, index;
char buffer[250] = {'\0'}, *tempval = NULL;


if (alias_string == NULL ||  info->alias_values == NULL)
return (1);

for (ind = 0; alias_string[ind] && alias_string[ind] != '='; ind++)
buffer[ind] = alias_string[ind];

tempval = fetch_alias(info, alias_string + ind + 1);

for (index = 0; info->alias_values[index]; index++)
{
if (str_compare(buffer, info->alias_values[index], ind) &&
info->alias_values[index][ind] == '=')
{

free(info->alias_values[index]);
break;
}
}


if (tempval)
{
buffer_add(buffer, "=");
buffer_add(buffer, tempval);
info->alias_values[index] = str_dup(buffer);
}
else
info->alias_values[index] = str_dup(alias_string);

return (0);
}
