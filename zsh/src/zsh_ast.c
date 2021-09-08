#include "header.h"

int zsh_cmd(global_t *global_info, char **cmd)
{
    if(strcmp(cmd[0], ZSH_CD_CMD) == 0)
    {
        zsh_cd(global_info, cmd[1]);
        return 0;
    } else if(strcmp(cmd[0], ZSH_PWD_CMD) == 0)
    {
        printf("%s\n", global_info->zsh_cwd);
        return 0;
    } else if(strcmp(cmd[0], ZSH_ECHO_CMD) == 0)
    {
        zsh_echo(global_info, cmd);
        return 0;
    } else if(strcmp(cmd[0], ZSH_ENV_CMD) == 0)
    {
        zsh_env(global_info);
        return 0;
    } else if(strcmp(cmd[0], ZSH_SETENV_CMD) == 0)
    {
        zsh_setenv(global_info, cmd);
        return 0;
    } else if(strcmp(cmd[0], ZSH_UNSETENV_CMD) == 0)
    {
        zsh_unsetenv(global_info, cmd);
        return 0;
    } else if(strcmp(cmd[0], ZSH_WHICH) == 0)
    {
        zsh_which(global_info, cmd);
        return 0;
    }
    return 1;
}

int zsh_ast(global_t *global_info, char **cmd)
{
        if
    (
        (strcmp(cmd[0], ZSH_EXIT) == 0) ||
        (strcmp(cmd[0], ZSH_QUIT) == 0)
    ) 
    {
        return 1;
    } else if(!zsh_cmd(global_info, cmd))
    {   
        return 0;
    } else
    {
        run_binary_cmd(global_info, cmd);
        return 0;
    }
}