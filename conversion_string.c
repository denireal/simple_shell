#include "shell.h"

/**
* str_length - This prints the length of a string.
* @string: string.
* Return: length of string.
*/
int str_length(char *s)
{
int length = 0;

if (s == NULL)
return (0);

while (s[length++] != '\0')
{
}
return (--length);
}

/**
* str_dup - This duplicates a string
* @string: String
* Return: pointer to the array
*/
char *str_dup(char *s)
{
char *val;
int length, ind = 0;

if (s == NULL)
return (NULL);

length = str_length(s) + 1;

val = malloc(sizeof(char) * length);

if (val == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}
for (; ind < length ; ind++)
{
val[ind] = s[ind];
}

return (val);
}

/**
* str_compare - This compare two or more strings
* @first_str: String one, or the shorter
* @second_str: String two, or the longer
* @number_char: number of characters to be compared
* Return: 1 if the strings are equals, 0 if the strings are not same
*/
int str_compare(char *first_str, char *second_str, int number_char)
{
int ind;

if (first_str == NULL && second_str == NULL)
return (1);

if (first_str == NULL || second_str == NULL)
return (0);

if (number_char == 0)
{
if (str_length(first_str) != str_length(second_str))
return (0);
for (ind = 0; first_str[ind]; ind++)
{
if (first_str[ind] != second_str[ind])
return (0);
}
return (1);
}
else
{
for (ind = 0; ind < number_char ; ind++)
{
if (first_str[ind] != second_str[ind])
return (0);
}
return (1);
}
}

/**
* str_concat - concatenates two or more strings.
* @first_str: First string to be concatenated
* @second_str: Second string to be concatenated
*
* Return: pointer to the array
*/
char *str_concat(char *first_str, char *second_str)
{
char *val;
int first_len = 0, second_len = 0;

if (first_str == NULL)
first_str = "";
first_len = str_length(first_str);

if (second_str == NULL)
second_str = "";
second_len = str_length(second_str);

val = malloc(sizeof(char) * (first_len + second_len + 1));
if (val == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}

/* copy of string1 */
for (first_len = 0; first_str[first_len] != '\0'; first_len++)
val[first_len] = first_str[first_len];
free(first_str);

/* copy of string2 */
for (second_len = 0; second_str[second_len] != '\0'; second_len++)
{
val[first_len] = second_str[second_len];
first_len++;
}

val[first_len] = '\0';
return (val);
}


/**
* str_reverse - reverses a string.
*
* @string: pointer to string.
* Return: void.
*/
void str_reverse(char *s)
{

int i = 0, length = str_length(s) - 1;
char store;

while (i < length)
{
store = s[i];
s[i++] = s[length];
s[length--] = store;
}
}
