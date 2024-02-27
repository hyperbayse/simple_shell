#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * struct builtin - Structure for built-in commands
 * @type: The name of the built-in command
 * @func: A function pointer to the built-in command function
 */
typedef struct builtin
{
	const char *type;
	void (*func)(char **);
}builtin;

/* Array of built-in commands */
extern builtin built_cmds[];
/* External environment variables */
extern char **environ;


int main(int ac, char *av[]);
int is_interactive_mode(int ac);
void interactive_mode(void);
void non_interactive_mode(int ac, char *av[]);
void process_input(char *input);
void alias_command(char **args);
void _free(char **arr);
void display_prompt(void);
const char *get_shell_name(void);
void handle_change_dir(char **args);
int print_built_ins(const char *command, char **argu);
void process_script_file(const char *filename);
void process_unatty_input(char *input_line);
void set_shell_name(const char *name);
char *c_getline(void);
ssize_t _getline(char **linept, size_t *n, FILE *stream);
int beginwith(const char *str, const char *pref);
char *strtrim(char *str);
char *remove_comment(char *line);
int handle_logical_operator(char *cmdline);
int execute_command(char *full_path, char **args);
int execute_operator(char *cmd, int *status);
char *store_operators(char *cmdline);
char *pars_command(char *input);
char **parse_arguments(char *input);
char **c_tokenize(char *input, const char *delimiters, int *token_count);
int execute_all_command(char *cmd, char **args);
char **construct_args(char *command, char **args);
char *c_tokenizer(char *str, const char *delimiters);
void handle_cmd_line(char *command_line);
int its_builtin_cmd(const char *cmd);
int is_whitespace(const char *str);
void handle_exit(char *put_line);
void handle_environment(char **args);
void handle_set_env(char **args);
void handle_unset_env(char **args);

/**
 * struct Alias - Structure to store aliases in the shell program
 * @name: Name of the alias, limited to 64 characters
 * @value: Value associated with the alias, limited to 128 characters
 * @next: Pointer to the next Alias in the linked list
 *
 */
typedef struct Alias
{
	char name[64];
	char value[128];
	struct Alias *next;
} Alias;
extern Alias *alias_list;

void define_alias(const char *name, const char *value);
void list_aliases(void);
void print_alias(const char *name);
void init_aliases(void);
void cleanup_aliases(void);

#endif
