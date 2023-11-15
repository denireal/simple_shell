#include "shell.h"

#define MAX_INPUT_SIZE 1024

/**
* tx_getline - Function reads a line from the command prompt.
* @progr_info: struct containing program information
*
* Return: count of bytes read.
*/
int tx_getline(progr_info *info)
{
static char buffer[MAX_INPUT_SIZE] = {'\0'};
static size_t buffer_position = 0;
static char *cmd_input[10] = {NULL};
static char cmd_oper[10] = {'\0'};
ssize_t read_bytes;
size_t cmd_index = 0;

/* Check if there are no more commands in the array or if the previous */
/* command was successful (based on logical operators) */
if (!cmd_input[0] || (cmd_oper[0] == '&' && errno != 0) ||
(cmd_oper[0] == '|' && errno == 0))
{
/* Free the memory allocated in the array if it exists */
for (cmd_index = 0; cmd_input[cmd_index]; cmd_index++)
{
free(cmd_input[cmd_index]);
cmd_input[cmd_index] = NULL;
}

/* Read from the file descriptor fd into the buffer */
if (buffer[buffer_position] == '\0')
{
read_bytes = read(info->fd, buffer, MAX_INPUT_SIZE - 1);
if (read_bytes <= 0)
{
return (-1); /* Error or end of file */
}
buffer[read_bytes] = '\0';
buffer_position = 0;
}

/* Split lines based on '\n' or ';' */
for (cmd_index = 0; cmd_input[cmd_index]; cmd_index++)
{
cmd_input[cmd_index] = str_dup(_strtok(cmd_index ? NULL : buffer +
buffer_position, "\n;"));
/* Check and split for '&&' and '||' operators */
cmd_index = check_split_ops(cmd_input, cmd_index, cmd_oper);
}
}

/* Obtain the next command (command 0) and remove it from the array */
info->input_line = cmd_input[0];
for (cmd_index = 0; cmd_input[cmd_index]; cmd_index++)
{
cmd_input[cmd_index] = cmd_input[cmd_index + 1];
cmd_oper[cmd_index] = cmd_oper[cmd_index + 1];
}

/* Update buffer position */
buffer_position += str_length(info->input_line);

return (str_length(info->input_line));
}
