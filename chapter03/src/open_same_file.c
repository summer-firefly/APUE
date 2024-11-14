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
int main() {
    int fd1 = open("./test.txt", O_RDWR | O_CREAT, 0666);
    int fd2 = open("./test.txt", O_RDWR | O_CREAT, 0666);
    write(fd1, "hello", 5);
    printf("fd1对应的文件指针指向的文件表项中文件偏移量为%ld\n", lseek(fd1, 0, SEEK_CUR));
    printf("fd2对应的文件指针指向的文件表项中文件偏移量为%ld\n", lseek(fd2, 0, SEEK_CUR));
    write(fd2, "123", 3);
    printf("fd1对应的文件指针指向的文件表项中文件偏移量为%ld\n", lseek(fd1, 0, SEEK_CUR));
    printf("fd2对应的文件指针指向的文件表项中文件偏移量为%ld\n", lseek(fd2, 0, SEEK_CUR));
    close(fd1);
    close(fd2);
    //test.txt中的文件内容为123lo
    return 0;
}