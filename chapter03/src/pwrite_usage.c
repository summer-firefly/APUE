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
void pwrite_usage(int offset, int fd) {
    pwrite(fd, "abc", 3, offset);
    printf("pwrite从偏移量为%d的位置写入数据后文件偏移量为%ld\n", offset, lseek(fd, SEEK_CUR, 0));
}
int main() {
    int fd = open("./test.txt", O_WRONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    printf("打开文件后偏移量为%ld\n", lseek(fd, SEEK_CUR, 0));
    pwrite_usage(2, fd);
    close(fd);
    return 0;
}