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
    int fd = open("./test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    write(fd, "123", 3); // 将数据从用户空间写入内核空间的缓冲区,会在适当的时机将内核空间的数据同步到磁盘
    fsync(fd);           // 立即将内核空间数据同步到磁盘
    close(fd);
    return 0;
}