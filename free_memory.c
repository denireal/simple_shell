#include "shell.h"

/**
* tx_free_mem - Deallocate memory for a double pointer and its dynamically
* created array of strings.
* @argv: Double pointer to an array of strings created dynamically using malloc.
* @number: Number of strings in the array to be released.
* Return: void
*/
void tx_free_mem(char **argv, unsigned int number)
{
unsigned int ind = 0;

if (argv != NULL)
{
while (ind < nnumber)
{
if (argv[ind] != NULL)
free(argv[ind]);
ind++;
}
free(argv);
}
}

/**
* tx_mem_dealloc - Release allocated memory resources.
* @token_array: Pointer to an array of strings.
* @path_value: Pointer to a string holding the PATH value.
* @input_line: Pointer to user input.
* @command_path: Pointer to the complete path.
* @is_dynamic_path: Indicates whether it is a dynamic path or not.
* Return: void
*/
void tx_mem_dealloc(char **token_array, char *path_value, char *input_line,
char *command_path, int is_dynamic_path)
{
switch (is_dynamic_path)
{
case 1:
if (command_path != NULL)
free(command_path);
// fall through to free other pointers
case 0:
if (token_array != NULL)
free(token_array);
if (input_line != NULL)
free(input_line);
break;
default:
break;
}

if (path_value != NULL)
free(path_value);
}
