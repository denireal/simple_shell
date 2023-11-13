#include "shell.h"

/**
 * _imprimit - This prints an array of chars in the stdout
 * @char_arr: pointer to the array of chars
 * Returns the count of written bytes or -1 on error,
 * with the error code set in the errno variable.
 */
int _imprimit(char *char_arr)
{
	return (write(STDOUT_FILENO, char_arr, str_length(char_arr)));
}
/**
 * _imprimo - This prints an array of chars in the stderr
 * @char_arr: pointer to the array of chars
 * Returns the count of written bytes or -1 on error,
 * with the error code set in the errno variable.
 */
int _imprimo(char *char_arr)
{
	return (write(STDERR_FILENO, char_arr, str_length(char_arr)));
}

/**
 * error_inprimo - This prints an array of chars in the stderr
 * @data: a pointer to the program's data'
 * @code_err: error code to print
 * Returns the count of written bytes or -1 on error,
 * with the error code set in the errno variable.
 */
int error_inprimo(int code_err, progr_info *info)
{
	char n_str[10] = {'\0'};

	long_string((long) info->execution_ctr, n_str, 10);

	if (code_err == 2 || code_err == 3)
	{
		_imprimo(info->progr_name);
		_imprimo(": ");
		_imprimo(n_str);
		_imprimo(": ");
		_imprimo(info->token_arr[0]);
		if (code_err == 2)
			_imprimo(": Invalid number: ");
		else
			_imprimo(": can't cd to ");
		_imprimo(info->token_arr[1]);
		_imprimo("\n");
	}
	else if (code_err == 127)
	{
		_imprimo(info->progr_name);
		_imprimo(": ");
		_imprimo(n_str);
		_imprimo(": ");
		_imprimo(info->the_cmd);
		_imprimo(": not available\n");
	}
	else if (code_err == 126)
	{
		_imprimo(info->progr_name);
		_imprimo(": ");
		_imprimo(n_str);
		_imprimo(": ");
		_imprimo(info->the_cmd);
		_imprimo(": Permission not granted\n");
	}
	return (0);
}
