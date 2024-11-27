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
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "需要指定一个文件描述符为命令行参数\n");
        return -1;
    }
    int flags = fcntl(atoi(argv[1]), F_GETFL, 0);
    if (flags == -1) {
        printf("fcntl获取文件描述符属性失败\n");
        return -1;
    }
    switch (flags & O_ACCMODE) {
    case O_RDONLY:
        printf("文件的访问模式为只读\n");
        break;
    case O_WRONLY:
        printf("文件的访问模式为只写\n");
        break;
    case O_RDWR:
        printf("文件的访问模式为读写\n");
        break;
    default:
        printf("文件访问模式错误\n");
        break;
    }
    if (flags & O_APPEND) {
        printf("文件描述符APPEND标志被打开\n");
    }
    if (flags & O_NONBLOCK) {
        printf("文件描述符NONBLOCK标志被打开\n");
    }
    if (flags & O_SYNC) {
        printf("文件描述符SYNC标志被打开\n");
    }
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (flags & O_FSYNC) {
        printf("FSYNC标志被打开\n");
    }
#endif
    return 0;
}