#include "shell.h"

#define UNUSED(x) (void)(x)

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
while (ind < number)
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
* @token_array: Pointer to an array of strings (unused).
* @path_value: Pointer to a string holding the PATH value.
* @input_line: Pointer to user input (unused).
* @command_path: Pointer to the complete path (unused).
* @is_dynamic_path: Indicates whether it is a dynamic path or not.
* Return: void
*/
void tx_mem_dealloc(char **token_array, char *path_value, char *input_line,
char *command_path, int is_dynamic_path)
{
unsigned int i;
void *pointers[3];
unsigned int num_pointers = sizeof(pointers) / sizeof(pointers[0]);

UNUSED(token_array);
UNUSED(input_line);
UNUSED(command_path);

pointers[0] = NULL;
pointers[1] = NULL;
pointers[2] = NULL;

for (i = 0; i < num_pointers; i++)
{
if ((i == (unsigned int)is_dynamic_path || is_dynamic_path == -1) && pointers[i] != NULL)
{
free(pointers[i]);
}
}

if (path_value != NULL)
free(path_value);
}
