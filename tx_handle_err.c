#include "shell.h"

/**
* tx_show_error - Display error messages based on the error code.
* @err_code: An integer representing the type of error.
* Return: void
*/

void tx_show_error(int err_code)
{
switch (err_code)
{
case 1:
write(STDERR_FILENO, FORK_PROC_ERR, tx_strlen(FORK_PROC_ERR));
perror("Error");
break;
case 2:
perror("Error");
break;
case 3:
write(STDERR_FILENO, MEM_ALLOC_ERR, tx_strlen(MEM_ALLOC_ERR));
break;
case 4:
write(STDERR_FILENO, NO_FILE_ERR, tx_strlen(NO_FILE_ERR));
break;
default:
break;
}
}
