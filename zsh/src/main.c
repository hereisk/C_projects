#include "header.h"

char **sort_argv(int *argc, char **argv)
{
    char **cmd = malloc(sizeof(cmd) * argc[0]);
    int i = 1;
    for(; i < argc[0]; i++)
    {
        cmd[i - 1] = _strdup(argv[i]);
    }
    cmd[i - 1] = NULL;
    return cmd;
}

int process_initial_input(int *argc, char **argv, global_t *global_info)
{
    char **cmd = sort_argv(argc, argv);
    run_binary_cmd(global_info, cmd);
    free_cmd(cmd);
    return 0;
}

int main(int argc, char **argv, char *envp[])
{

    global_t *global_info = init_global(envp);

    if(argc > 1)
    {
        process_initial_input(&argc, argv, global_info);
    }
    generate_zsh(global_info);

    free_global(global_info);
    return 0;
}