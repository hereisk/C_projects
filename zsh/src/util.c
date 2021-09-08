#include "header.h"

int _strcmp(char *string1, char *string2)
{
    for(; *string1 && *string2 && *string1 == *string2; string1++, string2++);
    return *string1 - *string2;
}

int _strlen(char *string)
{
    int i = 0;
    while(string[i] != '\0')
    {
        i++;
    }
    return i;
}

char *_strdup(char *source)
{
    char *copy = malloc(_strlen(source) + 1);
    int i = 0;
    for(; i < _strlen(source); i++)
    {
        copy[i] = source[i];
    }
    copy[i] = '\0';
    return copy;
}

//copy string to already allocated space. If the destination string is not empty, it gets cleared out
void copy_string(char *destination ,char* source)
{
    int i = 0;
    while(destination[i] != '\0')
    {
        destination[i] = '\0';
        i++;
    }
    i = 0;

    for(; i < _strlen(source); i++)
    {
        destination[i] = source[i];
    }
    destination[i] = '\0';
}

char *_getenv(global_t *global_info, char *env_name)
{
    int env_name_length = _strlen(env_name);
    int i = 0,
        j = 0,
        count = 0,
        flag = 0;
        while(global_info->zsh_env[i] != NULL)
        {
            for(; j < env_name_length; j++)
            {
                if(global_info->zsh_env[i][j] == env_name[j])
                {
                    count++;
                } else
                {
                    j = 0;
                    break;
                }
            }
            if(count == env_name_length)
            {
                flag = 1;
                break;
            }
            count = 0;
            i++;
        }
        
        if(flag == 1)
        {
            return _strdup(&global_info->zsh_env[i][j + 1]);
        } else
        {
            return _strdup("");
        }
}