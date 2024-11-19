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
    char buf[1024];
    int fd;
    buf[pread(fd = open("./test.txt", O_RDONLY), buf, 1024, 2)] = '\0';
    printf("读取到的内容为%s,使用pread读取之后文件偏移量为%ld\n", buf, lseek(fd, SEEK_CUR, 0));
    close(fd);
    return 0;
}