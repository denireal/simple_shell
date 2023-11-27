#include "shell.h"

/**
* get_len - Get the length of an integer.
* @number: The integer to measure.
*
* Return: The length of the integer.
*/
int get_len(int number)
{
unsigned int positive_number;
int length = 1;

if (number < 0)
{
length++;
positive_number = (unsigned int)(-number);
}
else
{
positive_number = (unsigned int)number;
}

while (positive_number > 9)
{
length++;
positive_number /= 10;
}

return (length);
}

/**
* int_to_str - Convert an integer to a string.
* @number: The integer to convert.
*
* Return: A dynamically allocated string representing the integer.
*/
char *int_to_str(int number)
{
unsigned int positive_number;
int length;
char *result;

length = get_len(number);
result = malloc(sizeof(char) * (length + 1));
if (result == NULL)
return NULL;

*(result + length) = '\0';

if (number < 0)
{
positive_number = (unsigned int)(-number);
result[0] = '-';
}
else
{
positive_number = (unsigned int)number;
}

length--;
do {
*(result + length) = (positive_number % 10) + '0';
positive_number /= 10;
length--;
} while (positive_number > 0);

return (result);
}

/**
* str_to_int - Convert a string to an integer.
* @str: The input string.
*
* Return: The converted integer.
*/
int str_to_int(char *str)
{
unsigned int count = 0, digits = 0, result = 0, sign = 1, multiplier = 1, i;

while (*(str + count) != '\0')
{
if (digits > 0 && (*(str + count) < '0' || *(str + count) > '9'))
break;

if (*(str + count) == '-')
sign *= -1;

if (*(str + count) >= '0' && *(str + count) <= '9')
{
if (digits > 0)
multiplier *= 10;
digits++;
}
count++;
}

for (i = count - digits; i < count; i++)
{
result = result + ((*(str + i) - '0') * multiplier);
multiplier /= 10;
}

return (result * sign);
}
