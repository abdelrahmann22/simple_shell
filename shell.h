#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

#define BUFSIZE 256
#define TOKSIZE 64
#define PRINT(c) (write(STDOUT_FILENO, c, strlen(c))
#define SUCCESS (1)
#define FAIL (-1)
#define NEUTRAL (0)

/**
 * struct shl_data - Global Data Structure
 * @line: the line input
 * @args: the arguments
 * @env: the environment
 * @error_msg: the error message
 * @cmd: the parsed command
 * @index: the index of the command
 * @oldpwd: the old pwd
 * 
 * Description: Global Data Structure
*/

typedef struct shl_data
{
	char *line;
	char **args;
	char **env;
	char *error_msg;
	char **cmd;
	unsigned long int index;
	char *oldpwd;
} shl_t;


/**
 * struct builtin - builtin commands
 * @cmd: the command
 * @f: the function
 * 
 * Description: builtin commands
*/

typedef struct builtin
{
	char *cmd;
	int (*f)(shl_t *data);
} builtin_t;

int read_line(shl_t *);
int parse_line(shl_t *);
int split_line(shl_t *);
int process_cmd(shl_t *);

char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);

char *_strcpy(char *dest, char *src);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
int free_data(shl_t *);

void *fill_an_array(void *a, int el, unsigned int len);
void signal_handler(int sig);
char *_getenv(char *path_name);
void index_cmd(shl_t *data);
void array_rev(char *arr, int len);

int _atoi(char *s);
char *_itoa(unsigned int n);
int intlen(int n);
int print_error(shl_t *data);
int write_history(shl_t *data);
int _isalpha(int c);

int abort_prog(shl_t *data);
int change_dir(shl_t *data);
int display_help(shl_t *data);
int handle_builtin(shl_t *data);
int check_builtin(shl_t *data);

int is_path_format(char *data);
void is_short_format(char *data);
int is_builtin(shl_t *data);

#endif
