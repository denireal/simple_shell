#include "shell.h"
/**
* rev_string - This reverses a string.
* @s: String to be reversed.
*/
void rev_string(char *s)
{
int length = 0, i, j;
char *str, temp;

/* Find the length of the string */
while (length >= 0)
{
if (s[length] == '\0')
break;
length++;
}
str = s;

/* Perform in-place reversal of the string */
for (i = 0; i < (length - 1); i++)
{
for (j = i + 1; j > 0; j--)
{
/* Swap characters */
temp = *(str + j);
*(str + j) = *(str + (j - 1));
*(str + (j - 1)) = temp;
}
}
}
