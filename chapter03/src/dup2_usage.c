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
    int fd = open("./text.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    write(fd, "1234", 4);    // fd文件表项v-node指针指向test.txt的v-node,此次写入操作写入到test.txt
    dup2(STDOUT_FILENO, fd); // fd文件表项被修改,fd与STDOUT_FILENO共用一个文件表项,STDOUT_FILENO文件表项中的v-node指针指向标准输出的v-node
    write(fd, "1234", 4);    // 此次写入操作写入到标准输出
    return 0;
}