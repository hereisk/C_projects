#include "header.h"

void zsh_setenv(global_t *global_info, char **cmd)
{
    int i = 0,
        j = 0,
        count = 0,
        flag = 0,
        var_len = _strlen(cmd[1]),
        val_len = _strlen(cmd[2]);

    while(global_info->zsh_env[i] != NULL)
    {
        for(; j < var_len; j++)
        {
            if(global_info->zsh_env[i][j] == '=')
            {
                break;
            }
            if((global_info->zsh_env[i][j] - cmd[1][j]) == 0)
            {
                count++;
            } else
            {
                break;
            }
        }
        if(count == var_len)
        {
            flag = 1;
            break;
        } else
        {
            j = 0;
            count = 0;
            i++;
        }
    }
    if(flag == 1)
    {
        free(global_info->zsh_env[i]);
    }
    global_info->zsh_env[i] = malloc(var_len + val_len + 2);
    for(j = 0; j < var_len; j++)
    {
        global_info->zsh_env[i][j] = cmd[1][j];
    }
    global_info->zsh_env[i][j] = '=';
    j++;
    for(int n = 0; n < val_len; n++, j++)
    {
        global_info->zsh_env[i][j] = cmd[2][n];
    }

    global_info->zsh_env[i][j] = '\0';
}

void zsh_unsetenv(global_t *global_info, char **cmd)
{
    int i = 0,
        j = 0,
        count = 0,
        flag = 0,
        var_len = _strlen(cmd[1]);

    while(global_info->zsh_env[i] != NULL)
    {
        for(; j < var_len; j++)
        {
            if(global_info->zsh_env[i][j] == '=')
            {
                break;
            }
            if((global_info->zsh_env[i][j] - cmd[1][j]) == 0)
            {
                count++;
            } else
            {
                break;
            }
        }
        if(count == var_len)
        {
            flag = 1;
            break;
        } else
        {
            j = 0;
            count = 0;
            i++;
        }
    }
    if(flag == 1)
    {
        free(global_info->zsh_env[i]);
    }
    if(i == ZSH_ENV_SIZE)
    {
        global_info->zsh_env[i] = NULL;
    } else
    {    
        while(global_info->zsh_env[i] && i < ZSH_ENV_SIZE)
        {
            global_info->zsh_env[i] = global_info->zsh_env[i+1];
            i++;
        }
    }
}