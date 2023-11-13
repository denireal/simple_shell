#include "shell.h"

/**
* tx_tokenizer - Separates the string into tokens using a designated delimiter
* @info: Pointer to the program's information
*
* This function tokenizes the input string based on the specified delimiter
* and stores the resulting tokens in an array. The array of tokens is then
* stored in the program's information structure.
*/
void tx_tokenizer(progr_info *info)
{
char *delimiter = " \t";
int i, j, token_count = 2, length;

length = str_length(info->input_line);

if (length && info->input_line[length - 1] == '\n')
info->input_line[length - 1] = '\0';

for (i = 0; info->input_line[i]; i++)
{
for (j = 0; delimiter[j]; j++)
{
if (info->input_line[i] == delimiter[j])
token_count++;
}
}

info->token_arr = malloc(token_count * sizeof(char *));
if (info->token_arr == NULL)
{
perror(info->progr_name);
exit(errno);
}

i = 0;
info->token_arr[i] = str_dup(_strtok(info->input_line, delimiter));
info->the_cmd = str_dup(info->token_arr[0]);

while (info->token_arr[i++])
{
info->token_arr[i] = str_dup(_strtok(NULL, delimiter));
}
}
