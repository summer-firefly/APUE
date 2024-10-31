#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char **argv) {
    int fd = open("notexist.txt", O_RDONLY);
    if (fd == -1) {
        printf("打开文件失败,错误码为 : %d\n", errno);
        printf("错误信息 : %s\n", strerror(errno));
        perror(argv[0]);
    } else {
        close(fd);
    }
    return 0;
}