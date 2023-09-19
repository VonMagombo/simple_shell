#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

/* for read or write buffers */
#define READ_BUFFER 1024
#define WRITE_BUFFER 1024
#define BUFFER_FLUSH -1

/* for command chaining */
#define _NORMAL	0
#define _OR		1
#define _AND    2
#define _CHAIN	3

/* for itoa_rep() */
#define SMALLCAPS   1
#define _UNSIGNED	2

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguments to pass into a function
 *@arg_c: a string generated from getline containing arguements
 *@av: an array of strings generated from arg_c
 *@path: a string path for the current command
 *@ac: the argument count
 *@line_count: the error count
 *@error_exit:  error code for exit()s
 *@flag_Line_Count: if on count this line of input
 *@fname: program filename
 *@status: return status of the last exec'd command
 *@cmd_buffer: address of pointer to cmd_buffer
 *@env: linked list local copy of _enviro
 *@_enviro: modified copy of _enviro from env
 *@node_alias: the alias node
 *@env_changed: on if _enviro was changed
 *@buffer_type: cmd_type ||, &&, ;
 *@readfhand: the fhand from which to read line input
 */
typedef struct pass_data
{
	char *arg_c;
	char **av;
	unsigned int line_count;
	int error_exit;
	char *path;
	int ac;
	int flag_Line_Count;
	char *fname;
	list_t *env;
	char **_enviro;
	int env_changed;
	list_t *node_alias;
	int status;
	char **cmd_buffer; 
	int buffer_type; 
	int readfhand;
} pass_args_t;

/**
 *struct builtin - stores builtin strings and other related functions
 *@type: builtin command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(pass_args_t *);
} builtin_tb;

/* _atoi_handler.c */
int _interact(pass_args_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* the_loop.c */
int buddie_loop(pass_args_t *, char **);
int seek_builtin(pass_args_t *);
void _find(pass_args_t *);
void _fork(pass_args_t *);

/* errorHandler.c */
void puts_error(char *);
int putchar_error(char);
int fhand_put(char c, int fd);
int fhand_puts(char *str, int fd);

/* outputHandler.c */
void _puts(char *);
int _putchar(char);
char *begins_with(const char *, const char *);
char *_strdup(const char *);

/* the_tokenizer.c */
char **_strtok(char *, char *);

/* parser.c */
int is_cmd(pass_args_t *, char *);
char *dup_char(char *, int, int);
char *seek_path(pass_args_t *, char *, char *);

/* linked_list.c */
list_t *add_node(list_t **, char *, int);
list_t *last_node_add(list_t **, const char *, int);
size_t print_str(const list_t *);
int del_node_index(list_t **, unsigned int);
void free_list(list_t **);

/* linked_list2.c */
size_t list_len(const list_t *);
char **get_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_prefix(list_t *, char *, char);
ssize_t node_index_getter(list_t *, list_t *);

/* memory.c */
char *_memset(char *, char, unsigned int);
void free_str(char **);
void *_realloc(void *, unsigned int, unsigned int);
int free_up(void **);

/* errorHandler2.c */
int atoi_err(char *);
void print_err(pass_args_t *, char *);
int print_dec(int, int);
char *itoa_rep(long int, int, int);
void erase_comment(char *);

/* alias.c */
int my_exit(pass_args_t *);
int Custom_cd(pass_args_t *);
int my_help(pass_args_t *);
int my_alias(pass_args_t *);

/*getter.c */
ssize_t getInput(pass_args_t *);
int _getline(pass_args_t *, char **, size_t *);
void sigIntHandler(int);

/* _getdata.c */
void clear_data(pass_args_t *);
void set_data(pass_args_t *, char **);
void free_data(pass_args_t *, int);

/* environ.c */
char *_getenv(pass_args_t *, const char *);
int my_env(pass_args_t *);
int my_setenv(pass_args_t *);
int Custom_unsetenv(pass_args_t *);
int env_list_populater(pass_args_t *);

/* setter.c */
char **get_env(pass_args_t *);
int _unsetenv(pass_args_t *, char *);
int _setenv(pass_args_t *, char *, char *);


/* vars.c */
int chain_deli(pass_args_t *, char *, size_t *);
int replace_alias(pass_args_t *);
int replace_var(pass_args_t *);

#endif