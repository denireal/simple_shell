#include "shell.h"

/**
* tx_strcpy - Copy a string from source to target.
* @target: The destination string.
* @origin: The source string to be copied.
*
* Return: A pointer to the destination string.
*/
char *tx_strcpy(char *target, char *origin)
{
int index;

for (index = 0; origin[index] != '\0'; index++)
target[index] = origin[index];
target[index] = '\0';
return (target);
}

/**
* tx_strcmp - Compare two strings of a specified length.
* @source_str: The source string.
* @comparison_str: The string to compare against.
* @length: The specified length to compare.
*
* Return: -1 if strings are not equal, 1 otherwise.
*/
int tx_strcmp(char *source_str, char *comparison_str, unsigned int length)
{
unsigned int comparison_length;
unsigned int i;

comparison_length = tx_strlen(comparison_str);
if (comparison_length != length)
return (-1);

i = 0;
while (source_str[i] != '\0' && comparison_str[i] != '\0')
{
if (source_str[i] != comparison_str[i])
return (1);
i++;
}
return (0);
}
