#include "shell.h"

/**
* assign_line - Assigns the line variable for get_line
* @line: Pointer to the buffer that stores the input string
* @line_size: Size of the line buffer
* @buffer: String that is read into the line
* @buffer_size: Size of the buffer
*/
void assign_line(char **line, size_t *line_size, char *buffer,
size_t buffer_size)
{
if (*line == NULL)
{
*line_size = (buffer_size > BUFF_CHUNKSIZE) ? buffer_size : BUFF_CHUNKSIZE;
*line = buffer;
}
else if (*line_size < buffer_size)
{
*line_size = (buffer_size > BUFF_CHUNKSIZE) ? buffer_size : BUFF_CHUNKSIZE;
*line = buffer;
}
else
{
_strcpy(*line, buffer);
free(buffer);
}
}

/**
* get_line - Get input from a stream
* @line: Pointer to the buffer that stores the input
* @line_size: Size of the line buffer
* @stream: Stream to read from
* Return: The number of bytes read
*/
ssize_t get_line(char **line, size_t *line_size, FILE *stream)
{
int read_result;
static ssize_t input_size;
ssize_t retval;
char *buffer;
char current_char = 'z';

if (input_size == 0)
fflush(stream);
else
return (-1);

input_size = 0;

buffer = malloc(sizeof(char) * BUFF_CHUNKSIZE);
if (buffer == NULL)
return (-1);

while (current_char != '\n')
{
read_result = read(STDIN_FILENO, &current_char, 1);

if (read_result == -1 || (read_result == 0 && input_size == 0))
{
free(buffer);
return (-1);
}

if (read_result == 0 && input_size != 0)
{
input_size++;
break;
}

if (input_size >= BUFF_CHUNKSIZE)
buffer = _realloc_mem(buffer, input_size, input_size + 1);

buffer[input_size] = current_char;
input_size++;
}

buffer[input_size] = '\0';
assign_line(line, line_size, buffer, input_size);
retval = input_size;

if (read_result != 0)
input_size = 0;

return (retval);
}
