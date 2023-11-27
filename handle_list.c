#include "shell.h"

/**
* sep_node_point - Creates a new separator node and appends it to
* the end of the list.
* @head: Pointer to the head of the separator list.
* @sep: Separator character to be added.
*
* Return: Pointer to the head of the updated list.
*/
list_sep *sep_node_point(list_sep **head, char sep)
{
list_sep *new, *temp;

new = malloc(sizeof(list_sep));
if (new == NULL)
return (NULL);

new->separator = sep;
new->next_n = NULL;
temp = *head;

if (temp == NULL)
{
*head = new;
}
else
{
while (temp->next_n != NULL)
temp = temp->next_n;
temp->next_n = new;
}

return (*head);
}

/**
* free_sep_list - Frees the memory allocated for the separator list.
* @head: Pointer to the head of the separator list.
*/
void free_sep_list(list_sep **head)
{
list_sep *temp;
list_sep *curr;

if (head != NULL)
{
curr = *head;
while ((temp = curr) != NULL)
{
curr = curr->next_n;
free(temp);
}
*head = NULL;
}
}

/**
* line_node_point - Creates a new line node and appends it to the
* end of the list.
* @head: Pointer to the head of the line list.
* @line: Line string to be added.
*
* Return: Pointer to the head of the updated list.
*/
l_list *line_node_point(l_list **head, char *line)
{
l_list *new, *temp;

new = malloc(sizeof(l_list));
if (new == NULL)
return (NULL);

new->line = line;
new->next_n = NULL;
temp = *head;

if (temp == NULL)
{
*head = new;
}
else
{
while (temp->next_n != NULL)
temp = temp->next_n;
temp->next_n = new;
}

return (*head);
}

/**
* free_line_list - Frees the memory allocated for the line list.
* @head: Pointer to the head of the line list.
*/
void free_line_list(l_list **head)
{
l_list *temp;
l_list *curr;

if (head != NULL)
{
curr = *head;
while ((temp = curr) != NULL)
{
curr = curr->next_n;
free(temp);
}
*head = NULL;
}
}
