#include "shell.h"

/**
* mem_dealloc_data - This frees fields at each iteration.
* @info: A struct containing the program's info.
* Return: void.
*/
void mem_dealloc_data(progr_info *info)
{
if (info->tokens)
mem_dealloc_array(info->token-arr);
if (info->input_line)
free(info->input_line);
if (info->the_cmd)
free(info->the_cmd);

info->input_line = NULL;
info->the_cmd = NULL;
info->token_arr = NULL;
}

/**
* dealloc_all_data - This free all field of the data
* @info: struct of the program's info
* Return: void
*/
void dealloc_all_data(progr_info *info)
{
if (info->fd != 0)
{
if (close(info->fd))
perror(info->progr_name);
}
mem_dealloc_data(info);
mem_dealloc_array(info->env_cpy);
mem_dealloc_array(info->alias_values);
}

/**
* mem_dealloc_array - this function frees each pointer of an array
* @array_ptr: An array of pointers
* Return: void
*/
void mem_dealloc_array(char **array_ptrv)
{
int ind;

if (array_ptr != NULL)
{
for (ind = 0; array_ptr[ind]; ind++)
free(array_ptr[ind]);

free(array_ptr);
array = NULL;
}
}
