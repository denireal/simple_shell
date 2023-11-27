#include "shell.h"

/**
* read_line - Read a line from the standard input.
* @eof_stat: Pointer to an integer indicating the end-of-file status.
*
* Return: A pointer to the read input line.
*/
char *read_line(int *eof_stat)
{
char *input_line = NULL;
size_t bufsize = 0;

*eof_stat = getline(&input_line, &bufsize, stdin);

return (input_line);
}
