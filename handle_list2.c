#include "shell.h"

/**
* add_variable_node - Adds a variable node at the end of a variable list.
* @head: Head of the linked list.
* @var_length: Length of the variable.
* @value: Value of the variable.
* @value_length: Length of the value.
* Return: Address of the head.
*/
list_var *add_variable_node(list_var **head, int var_length, char *value,
int value_length)
{
list_var *new_node, *temp_node;

new_node = malloc(sizeof(list_var));
if (new_node == NULL)
return (NULL);

new_node->var_len = var_length;
new_node->val_var = value;
new_node->val_len = value_length;

new_node->next_n = NULL;
temp_node = *head;

if (temp_node == NULL)
{
*head = new_node;
}
else
{
while (temp_node->next_n != NULL)
temp_node = temp_node->next_n;
temp_node->next_n = new_node;
}

return (*head);
}

/**
* free_variable_list - Frees a variable list.
* @head: Head of the linked list.
* Return: No return.
*/
void free_variable_list(list_var **head)
{
list_var *temp_node;
list_var *curr_node;

if (head != NULL)
{
curr_node = *head;
while ((temp_node = curr_node) != NULL)
{
curr_node = curr_node->next_n;
free(temp_node);
}
*head = NULL;
}
}
