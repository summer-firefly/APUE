#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
    int fd = open("./test.link", O_RDWR | __O_NOFOLLOW);
    if (fd < 0) {
        printf("打开了一个符号链接,open函数出错返回\n");
    } else {
        printf("打开的不是符号链接\n");
        close(fd);
    }
    return 0;
}