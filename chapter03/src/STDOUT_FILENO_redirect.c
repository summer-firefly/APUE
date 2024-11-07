#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    close(STDOUT_FILENO);
    int fd = open("test.txt", O_RDWR | O_CREAT);
    fprintf(stderr, "fd : %d\n", fd);
    printf("hello world");
    return 0;
}