#include "shell.h"

/**
* _memcpy - Copies information between void pointers.
* @dest: Destination pointer.
* @src: Source pointer.
* @size: Size of the destination pointer.
*
* Return: No return.
*/
void _memcpy(void *dest, const void *src, unsigned int size)
{
char *char_dest = (char *)dest;
const char *char_src = (const char *)src;
unsigned int i;

for (i = 0; i < size; i++)
char_dest[i] = char_src[i];
}

/**
* _realloc_mem - Reallocates a memory block.
* @ptr: Pointer to the memory previously allocated.
* @old_size: Size, in bytes, of the allocated space of ptr.
* @new_size: New size, in bytes, of the new memory block.
*
* Return: ptr.
* If new_size == old_size, returns ptr without changes.
* If malloc fails, returns NULL.
*/
void *_realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *new_ptr;

if (ptr == NULL)
return (malloc(new_size));

if (new_size == 0)
{
free(ptr);
return (NULL);
}

if (new_size == old_size)
return (ptr);

new_ptr = malloc(new_size);
if (new_ptr == NULL)
return (NULL);

if (new_size < old_size)
_memcpy(new_ptr, ptr, new_size);
else
_memcpy(new_ptr, ptr, old_size);

free(ptr);

return (new_ptr);
}

/**
* _realloc_array - Reallocates a memory block of an array.
* @arr: Double pointer to the memory previously allocated.
* @old_size: Size, in bytes, of the allocated space of arr.
* @new_size: New size, in bytes, of the new memory block.
*
* Return: arr.
* If new_size == old_size, returns arr without changes.
* If malloc fails, returns NULL.
*/
char **_realloc_array(char **arr, unsigned int old_size, unsigned int new_size)
{
char **new_arr;
unsigned int i;

if (arr == NULL)
return (malloc(sizeof(char *) * new_size));

if (new_size == old_size)
return (arr);

new_arr = malloc(sizeof(char *) * new_size);
if (new_arr == NULL)
return (NULL);

for (i = 0; i < old_size; i++)
new_arr[i] = arr[i];

free(arr);

return (new_arr);
}
