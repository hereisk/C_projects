#include "header.h"

char **init_zsh_env(char *envp[])
{
    char **zsh_env = malloc(sizeof(zsh_env) * ZSH_ENV_SIZE);
    int sizeof_env = 0;
    while(envp[sizeof_env] != NULL)
    {
        sizeof_env++;
    }
    for(int i = 0; i < ZSH_ENV_SIZE; i++)
    {
        if(i < sizeof_env)
        {
            zsh_env[i] = _strdup(envp[i]);
        } else
        {
            zsh_env[i] = NULL;
        }
    }
    return zsh_env;
}

void free_zsh_env(char *zsh_env[])
{
    int i = 0;
    while(zsh_env[i] != NULL)
    {
        free(zsh_env[i]);
        i++;
    }
    free(zsh_env);
}

void zsh_env(global_t *global_info)
{
    int i = 0;
    while(global_info->zsh_env[i] != NULL)
    {
        printf("%s\n", global_info->zsh_env[i]);
        i++;
    }
}