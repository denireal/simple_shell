#include "shell.h"

/**
* tx_readline - Read a line of input from a file stream.
* @file_input: The file stream to read input from.
*
* Return: A pointer to the read line.
*/
char *tx_readline(FILE *file_input)
{
char *input_line = NULL;
size_t input_length = 0;
ssize_t bytes_read = 0;

bytes_read = getline(&input_line, &input_length, file_input);
if (bytes_read == -1)
{
free(input_line);
exit(0);
}

return (input_line);
}

/**
* tx_split_string - Split a string into tokens.
* @str: The string to be split.
*
* Return: An array of tokens.
*/
char **tx_split_string(char *str)
{
char **token_array = NULL;
char *curr_token = NULL;
unsigned int num_tokens = 0;

if (str == NULL || DELIMS == NULL)
return (NULL);

token_array = malloc(sizeof(char *) * BUFF_CHUNKSIZE);
if (token_array == NULL)
return (NULL);

curr_token = strtok(str, DELIMS);
while (curr_token != NULL && num_tokens < BUFF_CHUNKSIZE - 1)
{
token_array[num_tokens++] = curr_token;
curr_token = strtok(NULL, DELIMS);
}
token_array[num_tokens] = NULL;

return (token_array);
}
