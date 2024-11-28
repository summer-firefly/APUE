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
#include <dirent.h>
int main() {
    char buf[16] = {0};
    int fd = open("./test.txt", O_RDWR | O_APPEND); // test.txt的内容为"123"
    off_t off = lseek(fd, SEEK_SET, 0);
    printf("目前文件指针偏移量为%ld\n", off);
    int len = read(fd, buf, 16);
    buf[len] = 0;
    printf("读取到的内容为%s\n", buf);
    off = lseek(fd, SEEK_SET, 0);
    printf("目前文件指针偏移量为%ld\n", off);
    write(fd, "abc", 3);
    close(fd);
    return 0;
}