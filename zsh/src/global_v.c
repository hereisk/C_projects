#include "header.h"

void free_global(global_t *global_info)
{
    free_zsh_env(global_info->zsh_env);
    //free(global_info->zsh_cwd);
    //free(global_info->zsh_prior_wd);
    free(global_info);
}

global_t *init_global(char *envp[])
{
    global_t *global_info = malloc(sizeof(global_t));
    global_info->zsh_cwd[0] = '\0';
    global_info->zsh_prior_wd[0] = '\0';
    global_info->zsh_env = init_zsh_env(envp);
    init_zsh_wd(global_info);
    return global_info;
}