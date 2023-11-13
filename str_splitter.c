#include "shell.h"

/**
 * _strtok - This separates strings using specified delimiters
 * @input_string: Pointer to the array received from tx_getline
 * @delimiters: Characters used as delimiters to split the string
 *
 * Return: A pointer to the created token
 */

char *_strtok(char *input_string, char *delimiters)
{
static char *str;
char *current_token;

if (input_string != NULL)
str = input_string;

while (*str != '\0')
{
int j;
for (j = 0; delimiters[j] != '\0'; j++)
{
if (*str == delimiters[j])
break;
}
if (delimiters[j] == '\0')
break;

str++;
}

current_token = str;

if (*current_token == '\0')
return (NULL);

while (*str != '\0')
{
int j;
for (j = 0; delimiters[j] != '\0'; j++)
{
if (*str == delimiters[j])
{
*str = '\0';
str++;
return (current_token);
}
}
str++;
}

return (current_token);
}
