#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#define PROMPT_MSG "TXSHELL-$ "
#define UNUSED __attribute__((unused))
#define BUFFER_SIZE 1024

/* ============ Strings for builtin help messages ============ */

/* General help message */
#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display and summarize builtin commands information.\n\n"\
"	If BUILTIN_NAME is specified, it gives detailed help on all \n"\
"	commands matching BUILTIN_NAME,\n"\
"	Else, it prints a list of help topics for BUILTIN_NAME.\n"\
" 	arguments:\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env_cpy\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

/* Help message for the "cd" command */
#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Modifies the current working directory.\n\n"\
"	If no directory is provided as an argument to cd,\n"\
"	it reads the command as cd $HOME.\n"\
"	If the argument is '-', then it reads it as cd $OLDPWD.\n\n"

/* Help message for the "env" command */
#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	Prints the environment.\n\n"\
"	This prints a comprehensive list of environment variables.\n\n"

/* Help message for the "exit" command */
#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exits the TX Shell.\n\n"\
"	If STATUS is specified, the exit status is set to N.\n"\
"	If N is not specified, the exit status becomes\n"\
"	the status of the last executed command.\n\n"

/* Help message for the "unsetenv" command */
#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	Removes one variable from the environment.\n\n"\
"	Error message is displayed when an invalid number of\n"\
"	arguments is specified.\n\n"

/* Help message for the "setenv" command */
#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Modifies an environment variable.\n\n"\
"	Initializes or modifies a new environment variable.\n"\
"	Error message is displayed when an invalid number of\n"\
"	arguments is specified.\n\n"

#endif
