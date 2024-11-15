#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <pthread.h>
int main() {
    int fd1 = open("./test.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    int fd2 = STDERR_FILENO;
    if (fd1 < 0) {
        perror("open");
        return -1;
    }
    const char *str = "hello world";
    write(fd1, str, strlen(str));
    printf("fd1对应文件表项中文件偏移量为%ld\n", lseek(fd1, 0, SEEK_CUR));
    printf("fd2对应文件表项中文件偏移量为%ld\n", lseek(fd2, 0, SEEK_CUR));
    dup2(fd1, fd2);
    if (lseek(fd2, 0, SEEK_CUR) == lseek(fd1, 0, SEEK_CUR)) {
        printf("调用dup2函数后fd1和fd2使用同一个文件表项\n");
        printf("调用dup2函数后fd2对应文件表项中文件偏移量为%ld\n", lseek(fd2, 0, SEEK_CUR));
    }
    close(fd1);
    return 0;
}