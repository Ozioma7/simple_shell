#ifndef _SHELL_MACROS
#define _SHELL_MACROS

#define MAX_TOKENS 64
#define MAX_TOKEN_SIZE 32
#define MAX_DIR_LENGTH 4096
#define BUF_SIZE 1024
#define DELIM " \n"

#define PROMPT "$ "
#define NOT_BUILTIN -99 /* If a command is not a builtin command */
#define COMMAND_ERROR -1

#define INTERACTIVE_MODE 99

/* Builtins */
#define BUILTIN_CD "cd"
#define BUILTIN_ENV "env"
#define BUILTIN_EXIT "exit"
#define BUILTIN_SETENV "setenv"
#define BUILTIN_UNSETENV "unsetenv"
#define BUILTIN_ALIAS "alias"

/* Logical operators */
#define LOGICAL_OR 1
#define LOGICAL_AND 2

#endif
