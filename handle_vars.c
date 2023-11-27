#include "shell.h"

/**
* check_env - Checks for environment variable and adds it to list_var list.
* @h: Head of list_var list.
* @in: Input string to check.
* @info: Shell information.
*/
void check_env(list_var **h, char *in, shell_info *info)
{
int row, chr, j, lval;
char **_envr;

_envr = info->_envvar;
for (row = 0; _envr[row]; row++)
{
for (j = 1, chr = 0; _envr[row][chr]; chr++)
{
if (_envr[row][chr] == '=')
{
lval = _strlen(_envr[row] + chr + 1);
add_variable_node(h, j, _envr[row] + chr + 1, lval);
return;
}

if (in[j] == _envr[row][chr])
j++;
else
break;
}
}

for (j = 0; in[j]; j++)
{
if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
break;
}

add_variable_node(h, j, NULL, 0);
}

/**
* check_vars - Checks for variables and adds them to list_var list.
* @h: Head of list_var list.
* @in: Input string to check.
* @st: Status string.
* @info: Shell information.
* Return: The length of the processed input.
*/
int check_vars(list_var **h, char *in, char *st, shell_info *info)
{
int i, lst, lpd;

lst = _strlen(st);
lpd = _strlen(info->pid);

for (i = 0; in[i]; i++)
{
if (in[i] == '$')
{
if (in[i + 1] == '?')
add_variable_node(h, 2, st, lst), i++;
else if (in[i + 1] == '$')
add_variable_node(h, 2, info->pid, lpd), i++;
else if (in[i + 1] == '\n' || in[i + 1] == '\0' || in[i + 1] == ' ' ||
in[i + 1] == '\t' || in[i + 1] == ';')
add_variable_node(h, 0, NULL, 0);
else
check_env(h, in + i, info);
}
}

return (i);
}

/**
* replaced_input - Replaces variables in the input string using list_var list.
* @list_var_head: Head of list_var list.
* @input: Original input string.
* @new_input: Buffer for the new input string.
* @new_len: Length of the new input string.
* Return: The modified input string.
*/
char *replaced_input(list_var **list_var_head, char *input, char *new_input,
int new_len)
{
list_var *list_var_index;
int i, j, k;

list_var_index = *list_var_head;
for (j = i = 0; i < new_len; i++)
{
if (input[j] == '$')
{
if (!(list_var_index->var_len) && !(list_var_index->val_len))
{
new_input[i] = input[j];
j++;
}
else if (list_var_index->var_len && !(list_var_index->val_len))
{
for (k = 0; k < list_var_index->var_len; k++)
j++;
i--;
}
else
{
for (k = 0; k < list_var_index->val_len; k++)
{
new_input[i] = list_var_index->val_var[k];
i++;
}
j += (list_var_index->var_len);
i--;
}
list_var_index = list_var_index->next_n;
}
else
{
new_input[i] = input[j];
j++;
}
}

return (new_input);
}

/**
* replace_variables - Replaces variables in the input string.
* @input: Original input string.
* @infosh: Shell information.
* Return: The modified input string.
*/
char *replace_variables(char *input, shell_info *infosh)
{
list_var *list_var_head, *list_var_index;
char *status, *new_input;
int original_len, new_len;

status = int_to_str(infosh->status);
list_var_head = NULL;

original_len = check_vars(&list_var_head, input, status, infosh);

if (list_var_head == NULL)
{
free(status);
return (input);
}

list_var_index = list_var_head;
new_len = 0;

while (list_var_index != NULL)
{
new_len += (list_var_index->val_len - list_var_index->var_len);
list_var_index = list_var_index->next_n;
}

new_len += original_len;

new_input = malloc(sizeof(char) * (new_len + 1));
new_input[new_len] = '\0';

new_input = replaced_input(&list_var_head, input, new_input, new_len);

free(input);
free(status);
free_variable_list(&list_var_head);

return (new_input);
}
