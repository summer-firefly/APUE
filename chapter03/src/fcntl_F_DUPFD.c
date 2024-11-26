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
void experiment1() {
    int fd = fcntl(STDOUT_FILENO, F_DUPFD);
    printf("使用fcntl复制文件描述符时不指定args参数,返回的文件描述符为%d\n", fd); // 如果不指定第三个参数,则dup fd失败,返回-1
    close(fd);
}
void experiment2() {
    int fd = fcntl(STDOUT_FILENO, F_DUPFD, 7, 8, 9);
    printf("使用fcntl复制文件描述符时指定args参数,返回的文件描述符为%d\n", fd); // 7号fd未被使用,返回7
    close(fd);
}
int main() {
    experiment1();
    experiment2();
    return 0;
}