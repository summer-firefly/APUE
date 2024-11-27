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
void show_fd_flag(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        return;
    }
    switch (flags & O_ACCMODE) {
    case O_RDONLY:
        printf("O_RDONLY标志打开\n");
        break;
    case O_WRONLY:
        printf("O_WRONLY标志打开\n");
        break;
    case O_RDWR:
        printf("O_RDWR标志打开\n");
        break;
    default:
        break;
    }
    if (flags & O_APPEND) {
        printf("O_APPEND标志打开\n");
    }
    if (flags & O_NONBLOCK) {
        printf("O_NONBLOCK标志打开\n");
    }
    if (flags & O_SYNC) {
        printf("O_SYNC标志打开\n");
    }
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (flags & O_FSYNC) {
        printf("O_FSYNC标志打开\n");
    }
#endif
}
void set_fd_flag(int fd, int flag) {
    int val;
    int set_result;
    printf("获取文件描述符标志\n");
    val = fcntl(fd, F_GETFL, 0);
    if (val < 0) {
        perror("fcntl");
        return;
    }
    printf("获取文件描述符标志成功,文件描述符标志如下:\n");
    show_fd_flag(fd);
    val |= flag; // set
    printf("set文件描述符标志\n");
    set_result = fcntl(fd, F_SETFL, val);
    if (set_result < 0) {
        perror("fcntl");
        return;
    }
    printf("set文件描述符标志成功,文件描述符标志如下:\n");
    show_fd_flag(fd);
}
void unset_fd_flag(int fd, int flag) {
    int val;
    int set_result;
    printf("获取文件描述符标志\n");
    val = fcntl(fd, F_GETFL, 0);
    if (val < 0) {
        perror("fcntl");
        return;
    }
    printf("获取文件描述符标志成功,文件描述符标志如下:\n");
    show_fd_flag(fd);
    val &= ~flag; // unset
    printf("unset文件描述符标志\n");
    set_result = fcntl(fd, F_SETFL, val);
    if (set_result < 0) {
        perror("fcntl");
        return;
    }
    printf("unset文件描述符标志成功,文件描述符标志如下:\n");
    show_fd_flag(fd);
}
int main() {
    set_fd_flag(STDOUT_FILENO, O_SYNC); // 在标准输出开启同步写标志
    printf("-------------------------------\n");
    set_fd_flag(STDIN_FILENO, O_NONBLOCK); // 开启标准输入的非阻塞模式
    printf("-------------------------------\n");
    unset_fd_flag(STDERR_FILENO, O_NONBLOCK); // 关闭标准输入的非阻塞模式
    return 0;
}