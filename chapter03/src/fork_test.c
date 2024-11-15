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
    int fd = open("./test.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    const char *str = "hello world";
    write(fd, str, strlen(str));
    printf("父进程文件表项中当前文件偏移量为%ld\n", lseek(fd, 0, SEEK_CUR));
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        printf("子进程文件表项中当前文件偏移量为%ld\n", lseek(fd, 0, SEEK_CUR));
        write(fd, "123", 3);
        printf("子进程写入数据后文件表项中当前文件偏移量为%ld\n", lseek(fd, 0, SEEK_CUR));
        exit(0);
    } else {
        wait(NULL);
    }
    printf("父进程在子进程写入数据后文件表项中当前文件偏移量为%ld\n", lseek(fd, 0, SEEK_CUR));
    close(fd);
    return 0;
}