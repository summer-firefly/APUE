#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main() {
    int fd = creat("./message.txt", 0666);
    if (fd == -1) {
        perror("create error");
        return -1;
    }
    write(fd, "hello world", strlen("hello world"));
    close(fd);
    return 0;
}