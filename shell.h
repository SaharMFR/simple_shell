#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

extern char **environ;

/**
 * struct SLL - Singly Linked List.
 * @nNodes: The number of nodes.
 * @str: The string in the node.
 * @next: Pointer to the next node.
 */
typedef struct SLL
{
	int nNodes;
	char *str;
	struct SLL *next;
} list_t;

/**
 * struct shellinfo - Contains information about the shell in that moment
 *	to be passed to any function to use them inside it.
 * @args: The entered string that contains command and arguments.
 * @argv: The array of command and arguments separated.
 * @argc: The number of elements in 'argv'.
 * @env: The local copy of environ (linked list).
 * @environ: The modified copy of environ using 'env' linked list.
 * @changed_env: If environment was changed.
 * @path: The path for the current command.
 * @nLine: The number of the line being executed to use in printing error.
 * @errNum: The number (code) to know the error.
 * @fileName: The file name of the program.
 * @inputLine: The number of input lines.
 * @status: The status returned from the last command.
 * @history: The history node of the current node.
 * @nHistory: The number of history lines.
 * @alias: The alias node.
 * @cmd_buf: The address of the pointer to cmd_buf (in chaining).
 * @cmd_type: The cmd buffer type.
 * @readfd: The file descriptor to read input line from.
 */
typedef struct shellinfo
{
	char *args;
	char **argv;
	int argc;
	list_t *env;
	char **environ;
	int changed_env;
	char *path;
	unsigned int nLine;
	int errNum;
	char *fileName;
	int inputLine;
	int status;
	list_t *history;
	int nHistory;
	list_t *alias;
	char **cmd_buf;
	int cmd_type;
	int readfd;
} info_t;

#define SHELL_INIT \
{NULL, NULL, 0, NULL, NULL, 0, NULL, 0, 0, NULL, 0, 0, NULL, 0, NULL, NULL, 0, 0};

/**
 * struct builtin - Contains pairs of functions and matching command.
 * @command: The string command.
 * @fun: The function to be executed.
 */
typedef struct builtin
{
	char *command;
	int (*fun)(info_t *);
} builtin_table;

int shellLoop(info_t *info, char **argv);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

char *_strcpy(char *destination, char *source);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *starts_with(const char *str, const char *toFind);
char *_strcat(char *destination, char *source);

int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int character);
int _atoi(char *str);

void _eputs(char *str);
int _eputchar(char c);
int _erratoi(char *str);
void print_error(info_t *info, char *error);
int print_d(int input, int fd);

int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buffer);

int is_cmd(info_t *info, char *path);
char *dup_chars(char *Path, int start, int stop);
char *find_path(info_t *info, char *Path, char *cmd);

void clear_info(info_t *info);
void set_info(info_t *info, char **argv);
void free_info(info_t *info, int freeAll);

char *_getenv(info_t *info, const char *name);
int _myenv(info_t *info);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int nLine);
int renumber_history(info_t *info);

list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **Head);

size_t list_len(const list_t *head);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *head);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

char *_Estrcpy(char *destination, char *source, int n);
char *_Estrcat(char *destination, char *source, int n);
char *_Estrchr(char *str, char c);

char *_memset(char *ptr, char Byte, unsigned int n);
void ffree(char **pptr);
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize);

int bfree(void **ptr);

char **strtoken(char *str, char *delim);
char **strtoken1(char *str, char delim);

int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int _myhistory(info_t *info);
int _myalias(info_t *info);

ssize_t get_input(info_t *info);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

int is_chain(info_t *info, char *buffer, size_t *pos);
void check_chain(info_t *info, char *buffer, size_t *pos, size_t start, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *New);


#endif
