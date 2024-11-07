#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
void example1() {
    char buf[1024];
    int fd = openat(-1, "/etc/os-release", O_RDONLY); // 使用绝对路径时,openat的第一个参数被忽略,等价于open
    int n = read(fd, buf, 1024);
    buf[n] = '\0';
    printf("%s\n", buf);
    close(fd);
}
void example2() {
    char buf[1024];
    int fd = openat(AT_FDCWD, "./test.txt", O_RDONLY); // 使用相对路径时,第一个参数表明"相对于谁",如果设置为AT_FDCWD,表明相对于当前目录
    int n = read(fd, buf, 1024);
    buf[n] = '\0';
    printf("%s\n", buf);
    close(fd);
}
void example3() {
    char buf[1024];
    int dirfd = open("/etc", O_RDONLY);
    int fd = openat(dirfd, "./os-release", O_RDONLY); // 使用相对路径时,第一个参数表明"相对于谁"
    int n = read(fd, buf, 1024);
    buf[n] = '\0';
    printf("%s\n", buf);
    close(fd);
    close(dirfd);
}
int main() {
    example1();
    example2();
    example3();
    return 0;
}