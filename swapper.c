#include "shell.h"

/**
* swap_special_char - swaps | and & for non-printed chars
*
* @input_line: input string
* @is_reverse: type of swap
* Return: swapped string
*/
char *swap_special_char(char *input_line, int is_reverse)
{
int i;

if (is_reverse == 0)
{
for (i = 0; input_line[i]; i++)
{
if (input_line[i] == '|')
{
if (input_line[i + 1] != '|')
input_line[i] = 16;
else
i++;
}

if (input_line[i] == '&')
{
if (input_line[i + 1] != '&')
input_line[i] = 12;
else
i++;
}
}
}
else
{
for (i = 0; input_line[i]; i++)
{
input_line[i] = (input_line[i] == 16 ? '|' : input_line[i]);
input_line[i] = (input_line[i] == 12 ? '&' : input_line[i]);
}
}
return (input_line);
}

/**
* add_separator_and_commands - add separators and command lines
* in the lists
*
* @head_sep: head of separator list
* @head_list: head of command lines list
* @input_line: input string
* Return: no return
*/
void add_separator_and_commands(list_sep **head_sep, l_list **head_list,
char *input_line)
{
int i;
char *line;

input_line = swap_special_char(input_line, 0);

for (i = 0; input_line[i]; i++)
{
if (input_line[i] == ';')
sep_node_point(head_sep, input_line[i]);

if (input_line[i] == '|' || input_line[i] == '&')
{
sep_node_point(head_sep, input_line[i]);
i++;
}
}

line = _strtok(input_line, ";|&");
do
{
line = swap_special_char(line, 1);
line_node_point(head_list, line);
line = _strtok(NULL, ";|&");
} while (line != NULL);
}

/**
* move_to_next - go to the next command line stored
*
* @l_sep: separator list
* @list_line: command line list
* @infosh: data structure
* Return: no return
*/
void move_to_next(list_sep **l_sep, l_list **list_line, shell_info *infosh)
{
int loop_sep;
list_sep *current_sep;
l_list *current_line;

loop_sep = 1;
current_sep = *l_sep;
current_line = *list_line;

while (current_sep != NULL && loop_sep)
{
if (infosh->status == 0)
{
if (current_sep->separator == '&' || current_sep->separator == ';')
loop_sep = 0;
if (current_sep->separator == '|')
current_line = current_line->next_n, current_sep = current_sep->next_n;
}
else
{
if (current_sep->separator == '|' || current_sep->separator == ';')
loop_sep = 0;
if (current_sep->separator == '&')
current_line = current_line->next_n, current_sep = current_sep->next_n;
}
if (current_sep != NULL && !loop_sep)
current_sep = current_sep->next_n;
}

*l_sep = current_sep;
*list_line = current_line;
}

/**
* split_command_exec - splits command lines according to
* the separators ;, | and &, and executes them
*
* @infosh: data structure
* @input_line: input string
* Return: 0 to exit, 1 to continue
*/
int split_command_exec(shell_info *infosh, char *input_line)
{

list_sep *head_sep_list, *current_sep_list;
l_list *head_cmd_list, *current_cmd_list;
int loop;

head_sep_list = NULL;
head_cmd_list = NULL;

add_separator_and_commands(&head_sep_list, &head_cmd_list, input_line);

current_sep_list = head_sep_list;
current_cmd_list = head_cmd_list;

while (current_cmd_list != NULL)
{
infosh->input_line = current_cmd_list->line;
infosh->arg_s = split_input(infosh->input_line);
loop = exec_cmdline(infosh);
free(infosh->arg_s);

if (loop == 0)
break;

move_to_next(&current_sep_list, &current_cmd_list, infosh);

if (current_cmd_list != NULL)
current_cmd_list = current_cmd_list->next_n;
}

free_sep_list(&head_sep_list);
free_line_list(&head_cmd_list);

if (loop == 0)
return (0);
return (1);
}

/**
* split_input - tokenizes the input string
*
* @input_line: input string.
* Return: string splitted.
*/
char **split_input(char *input_line)
{
size_t buffer_size;
size_t index;
char **split_tokens;
char *curr_token;

buffer_size = TOKEN_SIZE;
split_tokens = malloc(sizeof(char *) * (buffer_size));
if (split_tokens == NULL)
{
write(STDERR_FILENO, ": error in allocation\n", 18);
exit(EXIT_FAILURE);
}

curr_token = _strtok(input_line, DELIMITER);
split_tokens[0] = curr_token;

for (index = 1; curr_token != NULL; index++)
{
if (index == buffer_size)
{
buffer_size += TOKEN_SIZE;
split_tokens = _realloc_array(split_tokens, index, sizeof(char *) * buffer_size);
if (split_tokens == NULL)
{
write(STDERR_FILENO, ": error allocation\n", 18);
exit(EXIT_FAILURE);
}
}
curr_token = _strtok(NULL, DELIMITER);
split_tokens[index] = curr_token;
}

return (split_tokens);
}
