#include "shell.h"

/**
* _strcat - This joins two strings.
* @dest: Destination string.
* @src: Source string.
* Return: Pointer to the resulting string (dest).
*/
char *_strcat(char *dest, const char *src)
{
int dest_len = 0;
int src_index = 0;

while (dest[dest_len] != '\0')
{
dest_len++;
}

while (src[src_index] != '\0')
{
dest[dest_len] = src[src_index];
dest_len++;
src_index++;
}

dest[dest_len] = '\0';
return (dest);
}

/**
* _strcpy - This copies a string from source to destination.
* @dest: Destination string.
* @src: Source string.
* Return: Pointer to the resulting string (dest).
*/
char *_strcpy(char *dest, char *src)
{
size_t index = 0;

while (src[index] != '\0')
{
dest[index] = src[index];
index++;
}

dest[index] = '\0';

return (dest);
}

/**
* _strcmp - This compares two strings.
* @str1: First string.
* @str2: Second string.
* Return: 0 if strings are equal, positive if str1 > str2,
* negative if str1 < str2.
*/
int _strcmp(char *str1, char *str2)
{
int index = 0;

while (str1[index] == str2[index] && str1[index])
{
index++;
}

if (str1[index] > str2[index])
return (1);
if (str1[index] < str2[index])
return (-1);

return (0);
}

/**
* _strchr - This finds a character in a string.
* @str: String to search.
* @xter: Character to find.
* Return: Pointer to the first occurrence of the character
* in the string, or NULL if not found.
*/
char *_strchr(char *str, char xter)
{
unsigned int index = 0;

while (*(str + index) != '\0')
{
if (*(str + index) == xter)
return (str + index);
index++;
}

if (*(str + index) == xter)
return (str + index);

return ('\0');
}

/**
* _strspn - Gets the length of a prefix substring.
* @str: String to check.
* @accept: String containing the characters to match.
* Return: Number of characters in the initial segment of
* str that consist only of characters from accept.
*/
int _strspn(char *str, char *accept)
{
int str_index = 0;
int accept_index = 0;
int is_present;

while (*(str + str_index) != '\0')
{
is_present = 1;

while (*(accept + accept_index) != '\0')
{
if (*(str + str_index) == *(accept + accept_index))
{
is_present = 0;
break;
}

accept_index++;
}

if (is_present == 1)
break;

str_index++;
}

return (str_index);
}
