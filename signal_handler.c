#include "shell.h"

/**
* handle_interrupt_signal - Signal handler for SIGINT
* (interrupt signal).
*
* @signal_number: The signal number (in this case, SIGINT).
*/

void handle_interrupt_signal(int signal_num)
{
(void)signal_num;
write(STDOUT_FILENO, "\nTX_PROMPT$ ", 12);
}
