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
void printFileType(const char *filename) {
    struct stat st;
    if (lstat(filename, &st) == -1) {
        perror("lstat");
        return;
    }
    if (S_ISREG(st.st_mode)) {
        printf("%s是普通文件\n", filename);
    } else if (S_ISDIR(st.st_mode)) {
        printf("%s是目录\n", filename);
    } else if (S_ISCHR(st.st_mode)) {
        printf("%s是字符设备文件\n", filename);
    } else if (S_ISBLK(st.st_mode)) {
        printf("%s是块设备文件\n", filename);
    } else if (S_ISLNK(st.st_mode)) {
        printf("%s是符号链接\n", filename);
    } else if (S_ISFIFO(st.st_mode)) {
        printf("%s是FIFO\n", filename);
    } else if (S_ISSOCK(st.st_mode)) {
        printf("%s是套接字\n", filename);
    } else {
        printf("文件类型未知\n");
    }
}
int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("输入需要查看的文件\n");
        return -1;
    }
    for (int i = 1; i < argc; i++) {
        printFileType(argv[i]);
    }
    return 0;
}