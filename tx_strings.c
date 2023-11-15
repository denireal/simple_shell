#include "shell.h"

char *concatenated_string;

/**
* tx_strcat - Concatenate two strings.
* @target: The target string.
* @origin: The origin string to be appended to the target.
*
* Return: A pointer to the concatenated string.
*/
char *tx_strcat(char *target, char *origin)
{
char *result = target;

while (*target != '\0')
{
target++;
}

while (*origin != '\0')
{
*target = *origin;
target++;
origin++;
}
*target = '\0';
return (result);
}

/**
* tx_strdup - Duplicate a string.
* @s: The string to be duplicated.
*
* Return: A pointer to the duplicated string.
*/
char *tx_strdup(char *s)
{
char *duplicate;
int source_length = 0, i;

if (s == NULL)
return (NULL);

while (s[source_length] != '\0')
source_length++;

duplicate = (char *)malloc((source_length * sizeof(char)) + 1);
if (duplicate == NULL)
return (NULL);

for (i = 0; i < source_length; i++)
{
duplicate[i] = s[i];
}
duplicate[source_length] = '\0';

return (duplicate);
}

/**
* tx_strlen - Get the length of a string.
* @s: The input string.
*
* Return: The length of the string.
*/
unsigned int tx_strlen(const char *s)
{
unsigned int length = 0;

for (; *s++;)
length++;

return (length);
}

/**
* tx_strncmp - Compare the first n characters of two strings.
* @str1: The first string.
* @str2: The second string.
* @n: The number of characters to compare.
*
* Return: -1 if strings are not equal, 1 otherwise.
*/
unsigned int tx_strncmp(const char *str1, const char *str2, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
{
if (str1[i] != str2[i])
return (-1);
}

return (1);
}
