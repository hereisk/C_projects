#include "header.h"

#define ZSH_CD_DIR_UP ".."
#define ZSH_CD_MOVE_TO '/'
#define ZSH_CD_PREVIOUS_DIR "-"

void init_zsh_wd(global_t *global_info)
{
    char cwd[WD_SIZE];
    if(getcwd(cwd, WD_SIZE) == 0)
    {
        printf("Failed to generate current working directoly, zsh_cwd is '/'\n");
        copy_string(global_info->zsh_cwd ,"/");
        copy_string(global_info->zsh_prior_wd, "/");
    } else
    {
        copy_string(global_info->zsh_cwd, cwd);
        copy_string(global_info->zsh_prior_wd, cwd);
        chdir(global_info->zsh_cwd);
    }  

}

void zsh_cd_dir_up(global_t *global_info)
{
    copy_string(global_info->zsh_prior_wd, global_info->zsh_cwd);

    int cwd_len = _strlen(global_info->zsh_cwd);
    int i = 2;

    if(cwd_len > 1)
    {
        while(global_info->zsh_cwd[cwd_len - i] != '/')
        {
            global_info->zsh_cwd[cwd_len - i] = '\0';
            i++;
        }
    }
    chdir(global_info->zsh_cwd);
}

void zsh_cd_return_to_previous_dir(global_t *global_info)
{
    char temp_wd[WD_SIZE];
    copy_string(temp_wd, global_info->zsh_cwd);
    copy_string(global_info->zsh_cwd, global_info->zsh_prior_wd);
    copy_string(global_info->zsh_prior_wd, temp_wd);
    chdir(global_info->zsh_cwd);
}

void zsh_cd_move_to_location(global_t *global_info, char *dir)
{
    copy_string(global_info->zsh_prior_wd, global_info->zsh_cwd);
    copy_string(global_info->zsh_cwd, dir);
    chdir(global_info->zsh_cwd);
}

void zsh_cd_dir_down(global_t *global_info, char *dir)
{
    copy_string(global_info->zsh_prior_wd, global_info->zsh_cwd);

    int cwd_len = _strlen(global_info->zsh_cwd);
    global_info->zsh_cwd[cwd_len] = '/';
    cwd_len++;

    int i = 0;
    for(; i < _strlen(dir); i++)
    {
        global_info->zsh_cwd[cwd_len + i] = dir[i];
    }
    global_info->zsh_cwd[cwd_len + i] = '\0';
    chdir(global_info->zsh_cwd);
}

void zsh_cd(global_t *global_info, char *dir)
{
    if(!_strcmp(dir, ZSH_CD_DIR_UP))
    {
        zsh_cd_dir_up(global_info);

    } else if(!_strcmp(dir, ZSH_CD_PREVIOUS_DIR))
    {
        zsh_cd_return_to_previous_dir(global_info);

    } else if(!access(dir, X_OK)) //on success 0 is returned
    {
        if(dir[0] == ZSH_CD_MOVE_TO)
        {
            zsh_cd_move_to_location(global_info, dir);
        } else
        {
            zsh_cd_dir_down(global_info, dir);
        }
    } else
    {
        printf("cd: no such file or directory: %s, or the directory is not available\n", dir);
    }
}