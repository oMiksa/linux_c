#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd_fifo;
    char buff[100];
    
    unlink("./fifo0001.1");
    printf("%d\n", mkfifo("./fifo0001.1", O_RDWR));
    printf("%d\n", fd_fifo = open("./fifo0001.1", O_RDONLY));
  
while(scanf("%d")){
    
    printf("%d\n", read(fd_fifo, &buff, 100));
    
    printf("%s\n", buff);
    
    close(fd_fifo);
}

    return 0;
}


