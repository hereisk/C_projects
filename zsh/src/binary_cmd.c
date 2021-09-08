#include "header.h"
//------------------ Prototype of Error and Signa handling of a child process
void sort_signals(int signal)
{
    //printf("[%i] the process endded with a signal [%i]", signal, signal);

    
    switch(signal)
    {
        case SIGSEGV:
            printf("[%i] %s\n", signal, SIGSEGV_MESSAGE);
            break;
        default:
            printf("[%i] the process endded with a signal [%i]\n", signal, signal);
    }
    
}

//------------------ 
char *cwd_ex_path(global_t *global_info, char *cmd)
{
    int cwd_size = _strlen(global_info->zsh_cwd);
    int cmd_size = _strlen(cmd);
    int path_size = cwd_size + cmd_size - 1 + 1; 
    // -1 is to account for "." at the beginning of the executable command and +1 to account for '\0
    char cwd_ex_path[path_size];
    int k = 0;
    for(int i = 0; i < cwd_size; i ++)
    {
        cwd_ex_path[k] = global_info->zsh_cwd[i];
        k++;
    }
    for(int i = 1; i < cmd_size; i ++)
    {
        cwd_ex_path[k] = cmd[i];
        k++;
    }
    cwd_ex_path[k] = '\0';
    return _strdup(cwd_ex_path);
}

char *env_path(global_t *global_info, char *cmd)
{
    char *env_path = _getenv(global_info, "PATH");
    char path[_strlen(env_path) + 1];
    int i = 0, j = 0;

    for(; env_path[i] != '\0' ; i++)
    {
        if(env_path[i] == ':')
        {
            path[j] = '/';
            j++;
            for(int k = 0; k < _strlen(cmd); k++)
            {
                path[j] = cmd[k];
                j++;
            }
            path[j] = '\0';
            j = 0;
            if(access(path, 0) == 0)
            {
                free(env_path);
                return _strdup(path);
            }
        } else
        {
            path[j] = env_path[i];
            j++;
        }

    }
    free(env_path);
    return cwd_ex_path(global_info, cmd);
}

char *find_path(global_t *global_info, char *cmd)
{
    if(cmd[0] == '.' && cmd[1] == '/') //check if an executable file is sent
    {
        return cwd_ex_path(global_info, cmd);
    } else
    {
        return env_path(global_info, cmd);
    }
}

int run_binary_cmd(global_t *global_info, char **cmd)
{
  pid_t pid;
  int status;
  pid = fork();
  if (pid == 0)
  {
    // Child process
    char *path = find_path(global_info, cmd[0]);
//    printf("path is %s\n", path);

    if(execve(path, cmd, global_info->zsh_env) == -1)
    {
        perror("zsh");
    } else
    {
        free(path);
    }
    free_cmd(cmd);
    exit(EXIT_FAILURE);
  } else
  {
    // Parent process
    do
    {
        waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status)); // Wait for process child to be done.

    if(WIFSIGNALED(status) == 1) //if the child process ends with a signal
    {
        sort_signals(WTERMSIG(status));
    }
  }
  return 1;
}