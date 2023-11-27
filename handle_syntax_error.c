#include "shell.h"

/**
* repetition_char - Recursive function to check for repeated
* characters.
* @input: Pointer to the input string.
* @i: Counter for repetition.
* Return: Number of repeated characters.
*/
int repetition_char(char *input, int i)
{
if (*(input - 1) == *input)
return (repetition_char(input - 1, i + 1));

return (i);
}

/**
* sep_op_error - Check for syntax errors related to separators and
* operators.
* @input: Pointer to the input string.
* @i: Counter for error checking.
* @last: Last character encountered.
* Return: Index of the syntax error or 0 if no error.
*/
int sep_op_error(char *input, int i, char last)
{
int count;

count = 0;
if (*input == '\0')
return (0);

if (*input == ' ' || *input == '\t')
return (sep_op_error(input + 1, i + 1, last));

if (*input == ';')
if (last == '|' || last == '&' || last == ';')
return (i);

if (*input == '|')
{
if (last == ';' || last == '&')
return (i);

if (last == '|')
{
count = repetition_char(input, 0);
if (count == 0 || count > 1)
return (i);
}
}

if (*input == '&')
{
if (last == ';' || last == '|')
return (i);

if (last == '&')
{
count = repetition_char(input, 0);
if (count == 0 || count > 1)
return (i);
}
}

return (sep_op_error(input + 1, i + 1, *input));
}

/**
* first_char - Find the first non-whitespace character in the input.
* @input: Pointer to the input string.
* @i: Pointer to the counter.
* Return: 0 if a valid character is found, -1 if a separator or operator
* is found.
*/
int first_char(char *input, int *i)
{
for (*i = 0; input[*i]; *i += 1)
{
if (input[*i] == ' ' || input[*i] == '\t')
continue;

if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
return (-1);

break;
}

return (0);
}

/**
* print_syntax_error - Print syntax error message to STDERR.
* @infosh: Pointer to the shell_info struct.
* @input: Pointer to the input string.
* @i: Index of the syntax error.
* @bool: Flag indicating the direction of the error.
*/
void print_syntax_error(shell_info *infosh, char *input, int i, int bool)
{
char *separator, *prefix, *suffix, *error_msg, *line_counter;
int length;

if (input[i] == ';')
{
if (bool == 0)
separator = (input[i + 1] == ';' ? ";;" : ";");
else
separator = (input[i - 1] == ';' ? ";;" : ";");
}

if (input[i] == '|')
separator = (input[i + 1] == '|' ? "||" : "|");

if (input[i] == '&')
separator = (input[i + 1] == '&' ? "&&" : "&");

prefix = ": Syntax error: \"";
suffix = "\" unexpected\n";
line_counter = int_to_str(infosh->counter);
length = _strlen(infosh->arg_v[0]) + _strlen(line_counter);
length += _strlen(separator) + _strlen(prefix) + _strlen(suffix) + 2;

error_msg = malloc(sizeof(char) * (length + 1));
if (error_msg == 0)
{
free(line_counter);
return;
}

_strcpy(error_msg, infosh->arg_v[0]);
_strcat(error_msg, ": ");
_strcat(error_msg, line_counter);
_strcat(error_msg, prefix);
_strcat(error_msg, separator);
_strcat(error_msg, suffix);
_strcat(error_msg, "\0");

write(STDERR_FILENO, error_msg, length);
free(error_msg);
free(line_counter);
}

/**
* _syntax_error - Check for syntax errors in the input string.
* @infosh: Pointer to the shell_info struct.
* @input_line: Input string to check for errors.
* Return: 1 if syntax error found, 0 otherwise.
*/
int _syntax_error(shell_info *infosh, char *input_line)
{
int begin = 0;
int f_char = 0;
int i = 0;

f_char = first_char(input_line, &begin);
if (f_char == -1)
{
print_syntax_error(infosh, input_line, begin, 0);
return (1);
}

i = sep_op_error(input_line + begin, 0, *(input_line + begin));
if (i != 0)
{
print_syntax_error(infosh, input_line, begin + i, 1);
return (1);
}

return (0);
}
