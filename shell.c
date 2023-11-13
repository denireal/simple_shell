#include "shell.h"
/**
* main - Entry point, initializes program variables
* @argc: Number of command line arguments
* @argv: Array of command line argument values
* @env: Array of environment variable values
*
* Return: 0.
*/

int main(int argc, char *argv[], char *env_cpy[])
{
progr_info struct_info = {NULL}, *data = &struct_info;
char *tx_prompt = "";

initialize_struct(info, argc, argv, env);

signal(SIGINT, tx_newline);

if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
{
errno = 2;
tx_prompt = PROMPT_MSG;
}
errno = 0;
show_prompt(tx_prompt, info);
return (0);
}

/**
* tx_newline - Prints the prompt in a new line when sig is gotten
* @UNUSED: Placeholder for unused parameter in the prototype
*/

void tx_newline(int opr UNUSED)
{
_imprimit("\n");
_imprimit(PROMPT_MSG);
}

/**
* initialize_struct - Initializes the program's info structure
* @info: Pointer to the structure holding program info
* @argv: Array of arguments passed to the program execution
* @env_cpy: Environment passed to the program execution
* @argc: Number of args received from the command line
*/

void initialize_struct(progr_info *info, int argc, char *argv[], char **env_cpy)
{
int i = 0;

info->progr_name = argv[0];
info->input_line = NULL;
info->the_cmd = NULL;
info->execution_ctr = 0;

if (argc == 1)
info->fd = STDIN_FILENO;
else
{
info->fd = open(argv[1], O_RDONLY);
if (info->fd == -1)
{
_imprimit(info->progr_name);
_imprimit(": 0: Fail to open ");
_imprimit(argv[1]);
_imprimit("\n");
exit(127);
}
}
info->token_arr = NULL;
info->env_cpy = malloc(sizeof(char *) * 50);
if (env_cpy)
{
for (; env_cpy[i]; i++)
{
info->env_cpy[i] = str_dup(env_cpy[i]);
}
}
info->env_cpy[i] = NULL;
env_cpy = info->env_cpy;

info->alias_values = malloc(sizeof(char *) * 20);
for (i = 0; i < 20; i++)
{
info->alias_values[i] = NULL;
}
}
/**
* show_prompt - Displays the prompt in an infinite loop
* @tx_prompt: Prompt to be printed
* @info: Info relevant to the infinite loop
*/

void show_prompt(char *tx_prompt, progr_info *info)
{
int code_err = 0, string_len = 0;

while (++(info->execution_ctr))
{
_imprimit(tx_prompt);
code_err = string_len = tx_getline(info);

if (code_err == EOF)
{
dealloc_all_data(info);
exit(errno);
}
if (string_len >= 1)
{
alias_exps(info);
var_exps(info);
tx_parser(info);
if (info->token_arr[0])
{
code_err = execute(info);
if (code_err != 0)
error_inprimo(code_err, info);
}
mem_dealloc_data(info);
}
}
}
