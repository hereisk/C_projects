#ifndef HEADER
#define HEADER

#define BUFFER_SIZE 2
#define ZSH_LINE_SIZE 255
#define WD_SIZE 255
#define VALUE_SIZE 2550
#define ZSH_ENV_SIZE 255
#define CMD_LINE_PROMPT "my_zsh %>"
#define ZSH_EXIT "exit"
#define ZSH_QUIT "quit"

#define ZSH_CD_CMD "cd"
#define ZSH_PWD_CMD "pwd"
#define ZSH_ECHO_CMD "echo"
#define ZSH_ENV_CMD "env"
#define ZSH_SETENV_CMD "setenv"
#define ZSH_UNSETENV_CMD "unsetenv"
#define ZSH_WHICH "which"

#define SIGSEGV_MESSAGE "Invalid memory reference"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

typedef struct global
{   
    char **zsh_env;
    char zsh_cwd[WD_SIZE];
    char zsh_prior_wd[WD_SIZE];
} global_t;

int _strlen(char *string);
char *_strdup(char *source);
void copy_string(char *destination ,char* source);
char *_getenv(global_t *global_info, char *env_name);
int _strcmp(char *string1, char *string2);

int find_word(char *zsh_line, int i);
char **init_cmd(char *zsh_line, int *size_of_cmd);
void free_cmd(char **cmd);
int has_word(char *zsh_line);
int words_in_zsh_line(char *zsh_line);
int process_zsh_line(global_t *global_info, char *zsh_line, int* zsh_return);
int generate_zsh(global_t *global_info);

char *find_path(global_t *global_info, char *cmd);
int run_binary_cmd(global_t *global_info, char **cmd);
char *cwd_ex_path(global_t *global_info, char *cmd);


char **init_zsh_env(char *envp[]);
void free_zsh_env(char *zsh_env[]);
void print_zsh_env(char *zsh_env[]);

void free_global(global_t *global_info);
global_t *init_global(char *envp[]);
void free_global(global_t *global_info);

void init_zsh_wd(global_t *global_info);

void zsh_pwd(global_t *global_info);
void zsh_cd(global_t *global_info, char *dir);
void zsh_env(global_t *global_info);
char *find_env_echo(global_t *global_info, char **cmd);
void zsh_echo(global_t *global_info, char **cmd);

void zsh_setenv(global_t *global_info, char **cmd);
void zsh_unsetenv(global_t *global_info, char **cmd);

void zsh_which(global_t *global_info, char **cmd);
int zsh_ast(global_t *global_info, char **cmd);

#endif