#include "header.h"

char *find_env_echo(global_t *global_info, char **cmd)
{
    char *env_name = cmd[1];
    if(!_strcmp(cmd[0], "echo") && cmd[1][0] == '$')
    {
        env_name = &cmd[1][1];
    }

    int i = 0,
        j = 0,
        count = 0,
        var_len = _strlen(env_name);

    while(global_info->zsh_env[i] != NULL)
    {
        
        for(; j < var_len; j++)
        {
            if(global_info->zsh_env[i][j] == '=')
            {
                break;
            }
            if((global_info->zsh_env[i][j] - env_name[j]) == 0)
            {   
                count++;
            } else
            {
                break;
            }
        }
        if(count == var_len)
        {
            j += 1;
            return &global_info->zsh_env[i][j];
        } else
        {
            j = 0;
            count = 0;
            i++;
        }
    }
    return "";
}

void zsh_echo(global_t *global_info, char **cmd)
{
    if(cmd[1] == NULL)
    {
        printf("\n");
    } else if(cmd[1][0] == '$')
    {        
        printf("%s\n", find_env_echo(global_info, cmd));
    } else
    {
        int i = 1;
        while(cmd[i] != NULL)
        {
            printf("%s", cmd[i]);
            i++;
        }
        printf("\n");
    }
}