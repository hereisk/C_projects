#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define READLINE_READ_SIZE 8

struct my_read_s
{
    int bytes_read;
    int count;
    char buf[READLINE_READ_SIZE + 1];
};


char *my_readline(int fd)
{
    static struct my_read_s my_read_static = {0};
    struct my_read_s *my_read = &my_read_static;
    int i, j;

    if(my_read->count == 0)
    {
        my_read->bytes_read = read(fd, my_read->buf, READLINE_READ_SIZE);
        if(my_read->bytes_read <= 0 || (fd == 0 && my_read->bytes_read == 1))
        {
            return NULL;
        }
        my_read->buf[READLINE_READ_SIZE] = '\n';
        i = 0;
    }

    char *string = malloc(sizeof(string) * my_read->bytes_read);
    i = my_read->count;
    j = 0;
    for(; i < my_read->bytes_read; i++, j++)
    {
        if(my_read->buf[my_read->count] == '\n')
        {
            string[j] = my_read->buf[my_read->count];
            string[j+1] = '\0';
            my_read->count++;
            return string;
        }
        string[j] = my_read->buf[my_read->count];
        my_read->count++;
    }
    string[j] = '\0';
    my_read->count = 0;

    return string;
}

int main(int argc, char **argv)
{

    int fd = open(argv[1], O_RDONLY); // the file is open in read only mode

    if(fd == -1 && argc == 2)
    {
        return 1; // stop if a non-valid file name is passed
    } else if(fd == -1 && argc == 1)
    {
        fd = 0; // if no files pass then switch to reading from stdin
    }

    char *output = NULL;
    while ((output = my_readline(fd)) != NULL)
    {
        printf("%s", output);
        free(output);
    }
    close(fd);
    return 0;
}