#include "shell.h"

/**
* long_string - This converts a given number to a string.
* @num: number to be changed to a string.
* @buff_string: buffer to save the number as string.
* @base_num: base numbre to convert number
*
* Return: Void.
*/
void long_string(long num, char *buff_string, int base_num)
{
int ind = 0;
int val = 0;
long number = num;
char alphanumeric[] = {"0123456789abcdef"};

if (number == 0)
buff_string[ind++] = '0';

if (buff_string[0] == '-')
val = 1;

while (number)
{
if (number < 0)
buff_string[ind++] = alphanumeric[-(number % base_num)];
else
buff_string[ind++] = alphanumeric[number % base_num];
number /= base_num;
}
if (val)
buff_string[ind++] = '-';

buff_string[ind] = '\0';
str_reverse(s);
}

/**
* _atoi - This convert string to an integer.
*
* @str: pointer to str origin.
* Return: int of string or 0.
*/
int _atoi(char *s)
{
int signal = 1;
unsigned int a = 0;
/*1- analisys sign*/
while (!('0' <= *s && *s <= '9') && *s != '\0')
{
if (*s == '-')
signal *= -1;
if (*s == '+')
signal *= +1;
s++;
}
while ('0' <= *s && *s <= '9' && *s != '\0')
{

a = (a * 10) + (*s - '0');
s++;
}
return (a * signal);
}

/**
* count_characters - This count character in a string.
* @ptr_string: pointer to the origin of the string.
* @chars: string with  chars to be counted
* Return: INT or 0.
*/
int count_characters(char *ptr_string, char *chars)
{
int i, counter = 0;

for (i = 0; ptr_string[i]; i++)
{
if (ptr_string[i] == chars[0])
counter++;
}
return (counter);
}
