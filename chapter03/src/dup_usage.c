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
    int fd1 = open("./text.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    write(fd1, "1234", 4);
    printf("fd1的当前文件偏移量为%ld\n", lseek(fd1, 0, SEEK_CUR));
    printf("dup fd1,返回的文件描述符文件偏移量为%ld\n", lseek(dup(fd1), 0, SEEK_CUR));
    return 0;
}