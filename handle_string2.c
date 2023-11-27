#include "shell.h"

/**
* _strdup - Duplicates a string in dynamically allocated memory.
* @str: String to be duplicated.
* Return: Pointer to the newly allocated string.
*/
char *_strdup(const char *str)
{
char *duplicate;
size_t length;

length = _strlen(str);
duplicate = malloc(sizeof(char) * (length + 1));
if (duplicate == NULL)
return (NULL);
_memcpy(duplicate, str, length + 1);
return (duplicate);
}

/**
* _strlen - Calculates the length of a string.
* @str: String to find the length of.
* Return: Length of the string.
*/
int _strlen(const char *str)
{
int length;

for (length = 0; str[length] != 0; length++)
{
}
return (length);
}

/**
* cmp_chars - Compares characters in a string with a set of delimiters.
* @str: String to check.
* @delim: Delimiters to compare against.
* Return: 1 if all characters in str are delimiters, 0 otherwise.
*/
int cmp_chars(char str[], const char *delim)
{
unsigned int i, j, count;

for (i = 0, count = 0; str[i]; i++)
{
for (j = 0; delim[j]; j++)
{
if (str[i] == delim[j])
{
count++;
break;
}
}
}
if (i == count)
return (1);
return (0);
}

/**
* _strtok - Splits a string into tokens based on delimiters.
* @str: String to split.
* @delim: Delimiters to use for splitting.
* Return: Pointer to the next token, or NULL if no more tokens are found.
*/
char *_strtok(char str[], const char *delim)
{
static char *split_start, *str_end;
char *token_start;
unsigned int i, found_token;

if (str != NULL)
{
if (cmp_chars(str, delim))
return (NULL);
split_start = str; /* Store the first address */
i = _strlen(str);
str_end = &str[i]; /* Store the last address */
}
token_start = split_start;
if (token_start == str_end) /* Reaching the end */
return (NULL);

for (found_token = 0; *split_start; split_start++)
{
if (split_start != token_start && *split_start && *(split_start - 1) == '\0')
break;

for (i = 0; delim[i]; i++)
{
if (*split_start == delim[i])
{
*split_start = '\0';
if (split_start == token_start)
token_start++;
break;
}
}

if (found_token == 0 && *split_start) /* Str != Delim */
found_token = 1;
}

if (found_token == 0) /* Str == Delim */
return (NULL);
return (token_start);
}

/**
* _isnumber - Checks if a string represents a valid integer number.
* @str: String to check.
* Return: 1 if str is a number, 0 otherwise.
*/
int _isnumber(const char *str)
{
unsigned int i;

for (i = 0; str[i]; i++)
{
if (str[i] < '0' || str[i] > '9')
return (0);
}
return (1);
}
