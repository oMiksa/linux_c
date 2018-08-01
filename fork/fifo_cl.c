#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd_fifo;
    char buff[100] = "Hello";
    

    printf("%d\n", fd_fifo = open("./fifo0001.1", O_WRONLY));

    write(fd_fifo, buff, 100);

    close(fd_fifo);

    return 0;
}