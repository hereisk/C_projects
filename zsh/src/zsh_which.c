#include "header.h"

char *zsh_which_path(global_t *global_info, char *cmd)
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
    return _strdup("");
}


void zsh_which(global_t *global_info, char **cmd)
{
    if
    (
        (strcmp(cmd[1], ZSH_CD_CMD) == 0) ||
        (strcmp(cmd[1], ZSH_ECHO_CMD) == 0) ||
        (strcmp(cmd[1], ZSH_ENV_CMD) == 0) ||
        (strcmp(cmd[1], ZSH_SETENV_CMD) == 0) ||
        (strcmp(cmd[1], ZSH_UNSETENV_CMD) == 0) ||
        (strcmp(cmd[1], ZSH_PWD_CMD) == 0) ||
        (strcmp(cmd[1], ZSH_WHICH) == 0)
    )
    {
        printf("%s: shell built-in command\n", cmd[1]);
    } else
    {
        char *path = find_path(global_info, cmd[1]);
        if(_strlen(path) == 0)
        {
            printf("%s not found\n", cmd[1]);
        } else
        {
            printf("%s\n", path);
        }
        free(path);
    }
}