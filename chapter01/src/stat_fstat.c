#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void stat_usage() {
    struct stat statBuf;
    stat("README.md",&statBuf);
    printf("文件大小：%ld byte\n",statBuf.st_size);
}
void fstat_usage() {
    struct stat statBuf;
    int fd = open("README.md",O_RDONLY);
    fstat(fd,&statBuf);
    close(fd);
    printf("文件大小：%ld byte\n",statBuf.st_size);
}
int main() {
    printf("stat函数的使用\n");
    stat_usage();
    printf("fstat函数的使用\n");
    fstat_usage();
    return 0;
}