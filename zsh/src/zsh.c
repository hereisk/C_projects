#include "header.h"

int find_word(char *zsh_line, int i)
{
    //finds the beginning of a word if there is a series of spaces in of zsh_line
    while(zsh_line[i] == ' ' || zsh_line[i] == '\0' )
    {
        i++;
    }
    return i;
}

char **init_cmd(char *zsh_line, int *size_of_cmd)
{
    char word[_strlen(zsh_line) + 1];
    int k = 0, n = 0;
    char **cmd = malloc(sizeof(cmd) * size_of_cmd[0]);
    
    for(int i = find_word(zsh_line, 0); i < _strlen(zsh_line); i++)
    {
        while(zsh_line[i] != ' ' && zsh_line[i] != '\0')
        {
            word[k] = zsh_line[i];
            k++;
            i++;
        }
        word[k] = '\0';
        cmd[n] = _strdup(word);
        n++;
        k = 0;
        if(zsh_line[i] == ' ')
        {
            i = find_word(zsh_line, i);
        }
        //needs to decrement i to account for the increamentation of the for-loop
        i--;
    }
    cmd[size_of_cmd[0] - 1] = NULL;
    return cmd;
}

void free_cmd(char **cmd)
{
   for(int i = 0; cmd[i] != NULL; i++)
    {
        free(cmd[i]);
    }
    free(cmd);
}

int has_word(char *zsh_line)
{
    int i = 0;
    while(zsh_line[i] != '\0')
    {
        if(zsh_line[i] != ' ')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int words_in_zsh_line(char *zsh_line)
{
    int word_count = 0;

    for(int i = find_word(zsh_line, 0); i < _strlen(zsh_line); i++)
    {
        if(
            (zsh_line[i] == ' ' && zsh_line[i+1] != ' ') 
            && (zsh_line[i] == ' ' && zsh_line[i+1] != '\0')
            )
            word_count++;
    }
    word_count++;
    return word_count;
}

int process_zsh_line(global_t *global_info, char *zsh_line, int* zsh_return)
{
    int size_of_cmd = words_in_zsh_line(zsh_line) + 1;
    if(size_of_cmd == 1) return 0;
    char **cmd = init_cmd(zsh_line, &size_of_cmd);

    zsh_return[0] = zsh_ast(global_info, cmd);
    free_cmd(cmd);
    return 0;
}

int generate_zsh(global_t *global_info)
{
    int b_read,
        n_flag = 0,
        index = 0,
        zsh_return = 0;

    char buffer[BUFFER_SIZE];
    char zsh_line[ZSH_LINE_SIZE];


    while(zsh_return == 0)
    {
        write(0, CMD_LINE_PROMPT, strlen(CMD_LINE_PROMPT));
        while(n_flag == 0)
        {
            b_read = read(0, buffer, BUFFER_SIZE);
            for(int i = 0; i < b_read; i++)
            {
                if(buffer[i] != '\n')
                {
                    zsh_line[index] = buffer[i];
                    index++;
                } else
                {
                    zsh_line[index] = '\0';
                    index = 0;
                    n_flag = 1;
                }
            }
        }
        n_flag = 0;
        if(has_word(zsh_line))
        {
            process_zsh_line(global_info, zsh_line, &zsh_return);
        }
    }
    return 0;
}