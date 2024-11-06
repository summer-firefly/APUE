#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
    int fd = open("./test.txt", O_RDWR | O_CREAT | O_EXCL);
    if (fd < 0) {
        printf("文件已经存在,此次open调用没有新建文件\n");
    } else {
        printf("文件不存在,此次open调用新建文件\n");
        close(fd);
    }
    return 0;
}