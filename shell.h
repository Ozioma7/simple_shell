#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

#include "shell_macros.h"

extern char **environ;
extern int errno;

/**
 * struct al - alias data
 * @name: name of alias
 * @value: value to replace it with
 * @next: pointer to next node
 */
typedef struct al
{
	char *name;
	char *value;
	struct al *next;
} alias_list;

/**
 * struct od - Operation Data
 * @operands: The operands in the operation
 * @operators: The operators in the operation
 */
typedef struct od
{
	char **operands;
	int operators[MAX_TOKENS];
} ops_data;

/**
 * struct pd - Program Data
 * @name: Path of the shell when ran
 * @execution_count: Tracks the number of commands executed
 * @cmd: The current running command
 * @args: Current command arguments
 * @cmdline: The command read from stdin
 * @cmdlist: The commands available in a command line
 * @logic_data: Data related to the logical operation of a single command.
 * @al: Alias list
 * @cmdlinebuf: Buffer to store the expanded cmd line
 * @fd: File descriptor
 * @mode: Shell mode
 */
typedef struct pd
{
	char *name;
	int execution_count;
	char *cmd;
	char **args;
	char *cmdline;
	char **cmdlist;
	char cmdlinebuf[MAX_DIR_LENGTH];
	ops_data *logic_data;
	alias_list *al;
	int fd;
	int mode;

} shell_info;

/**
 * struct bf - Builtin-function
 * @cmd: The builtin command
 * @action: The function to handle the command
 */
typedef struct bf
{
	char *cmd;
	int (*action)(shell_info *data);
} builtin_action;

/*string functions*/
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
size_t _strlen(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *str);
int _strcmp(char *s1, char *s2);
char *_strtok(char *s, char *delim);
char *_strdup_range(char *src, int from, int to);
char *_strtrim(char *str);
int _isdigit(char *s);

/* other relevant functions */
void free_array_of_pointers(char **arr);
void free_program_data(shell_info *data);
void free_all_data(shell_info *data);
void free_aliases(alias_list *var);

/* command line interpreter functions */
ssize_t read_line(shell_info *data);
void show_prompt(shell_info *data);
void tokenize_input(shell_info *data);
char *handle_path(char *args);
int check_exec(char *args);
int exec_command(shell_info *data);
void shell_loop(shell_info *data);
int is_builtin(shell_info *data);
void init_data(shell_info *data);
void build_command_list(shell_info *data);
int check_comment(shell_info *data);
ops_data *expand_logical_ops(char *cmd, ops_data *data);
char *expand_variables(char *line, shell_info *data);
char *expand_alias(char *str, int ret, shell_info *data);

/* environment funtions */
char *_getenv(const char *name);
int _setenv(char *var, char *val);
int _unsetenv(char *var);

/* Builtin command handlers */
int print_environment(shell_info *data);
int builtin_exit(shell_info *data);
int builtin_setenv(shell_info *data);
int builtin_unsetenv(shell_info *data);
int builtin_cd(shell_info *data);
int builtin_alias(shell_info *data);

/* additonal alias functions */
void add_alias(char *name, char *value, shell_info *data);
void print_alias(shell_info *data, char *names);
alias_list *get_alias(shell_info *data, char *name);

/* Output */
void print_error(shell_info *data);
ssize_t _print_err(char *err);

/* Converters */
void number_to_string(char *buf, int num);
void reverse_string(char *str);
int _atoi(char *str);

/* Signal handlers */
void handle_sigint(int signal);

#endif
