#ifndef SHELL_HEADER
#define SHELL_HEADER

/*Headers*/
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/*Global constants & Definitions*/
#define EXT_COMMANDS 1
#define PATH_COMMANDS 3
#define INT_COMMANDS 2
#define INVALID_COMMANDS -1
#define min(x, y) (((x) < (y)) ? (x) : (y))

/*global vars*/
extern char *name_of_shell;
extern char *line;
extern int status;
extern char **environment;
extern char **commands;

/**
 * struct function_map - struct that matches a command to a function
 * @comm_name: name of command
 * @func: function that executes a command
 */

typedef struct function_map
{
	char *comm_name;
	void (*func)(char **command);
} func_map;


/*main functions*/
extern void handle_non_interactive_mode(void);
extern void init(char **curr_command, int command_type);

/*string functions*/
char **tokenize(char *, char *);
char *_strconcat(char *, char *);
char *_strchr(char *, char *);
char *_strtok_r(char *, char *, char *);
char *check_path(char *);

/*utilities*/
int comm_parser(char *);
char *_getenv(char *);
void exec_comm(char **, int);
void (*get_func(char *))(char **);

/*built in funcs*/
void quit(char **);
void env(char **);

/*Aux functions*/
void print(char *, int);
void rmv_ln(char *);
int _strlength(char *);
void _strcopy(char *, char *);

/*Aux functions2*/
int _strcmp(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);

/*Handlers*/
int _atoi(char *);
void *_mem_realloc(void *ptr, unsigned int prev, unsigned int curr);
void rmv_comment(char *);
void handle_ctrl_c(int);


#endif

