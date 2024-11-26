#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
    int fd = open("example.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 使用fcntl获取文件状态标志
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 检查文件的访问模式
    switch (flags & O_ACCMODE) {
    case O_RDONLY:
        printf("File is opened in read-only mode.\n");
        break;
    case O_WRONLY:
        printf("File is opened in write-only mode.\n");
        break;
    case O_RDWR:
        printf("File is opened in read-write mode.\n");
        break;
    default:
        printf("Unknown access mode.\n");
        break;
    }

    close(fd);
    return 0;
}
