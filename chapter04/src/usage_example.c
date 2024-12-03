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
void stat_usage() {
    struct stat st;
    stat("/usr/include/stdio.h", &st);
    printf("stat usage\n");
    printf("stdio.h文件大小为%ld字节\n", st.st_size);
    // 创建符号链接指向stdio.h
    symlink("/usr/include/stdio.h", "./stdio.link");
    stat("./stdio.link", &st); // stat函数会读取符号链接指向的实际文件的属性
    printf("符号链接指向的实际文件的大小为%ld字节\n", st.st_size);
    unlink("./stdio.link");
}
void lstat_usage() {
    struct stat st;
    // 创建符号链接指向stdio.h
    symlink("/usr/include/stdio.h", "./stdio.link");
    lstat("./stdio.link", &st); // lstat函数会读取符号链接本身的属性
    printf("符号链接的大小为%ld字节\n", st.st_size);
    unlink("./stdio.link");
}
void fstat_usage() {
    struct stat st;
    for (int i = 0; i < 3; i++) {
        if (fstat(i, &st)) {
            perror("fstat");
            return;
        }
        printf("%d号文件描述符对应的设备大小为%ld\n", i, st.st_size);
        printf("%d号文件描述符对应的文件i-node编号为%ld\n", i, st.st_ino);
    }
}
void fstatat_usage() {
    struct stat st;
    int dirfd = open("/usr/include", O_RDONLY | O_DIRECTORY); // O_DIRECTORY表示打开目录
    if (dirfd == -1) {
        perror("open");
        return;
    }
    fstatat(dirfd, "./stdio.h", &st, AT_SYMLINK_NOFOLLOW); // AT_SYMLINK_NOFOLLOW表示目标如果是符号链接,不更随
    printf("文件大小为%ld\n", st.st_size);
    close(dirfd);
}
int main() {
    // stat_usage();
    // lstat_usage();
    // fstat_usage();
    fstatat_usage();
    return 0;
}