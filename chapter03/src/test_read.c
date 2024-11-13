#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
void read_return_success() {
    const char *message = "hello world";
    int fd = open("./test.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    write(fd, message, strlen(message));
    lseek(fd, 0, SEEK_SET);
    char buf[1024];
    ssize_t len = read(fd, buf, 1023);
    printf("期望读取1023 Bytes,实际读取了%ld Bytes\n", len);
    buf[len] = '\0';
    printf("读取的内容是:%s\n", buf);
    close(fd);
}
void read_return_error() {
    char buf[1024];
    ssize_t len = read(-1, buf, 1023);
    if (len == -1) {
        perror("read");
    }
}
void read_return_zero() {
    int fd = open("./test.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    char buf[1024];
    ssize_t len = read(fd, buf, 1023);
    printf("期望读取1023 Bytes,实际读取了%ld Bytes\n", len);
    buf[len] = '\0';
    printf("读取的内容是:%s\n", buf);
    // read返回0不会改变文件描述符的偏移量
    printf("期望读取1023 Bytes,实际读取了%ld Bytes\n", len);
    buf[len] = '\0';
    printf("读取的内容是:%s\n", buf);
    close(fd);
}
void read_from_stdin() {
    // read函数从stdin读取数据时,会读取一行,包括空格
    char buf[1024];
    ssize_t len = read(0, buf, 1023);
    printf("期望读取1023 Bytes,实际读取了%ld Bytes\n", len);
    buf[len] = '\0';
    if (buf[len - 1] == '\n') {
        printf("read函数将'\\n'也进行读取\n");
    }
    printf("读取的内容是:%s", buf);
}
int main() {
    // read_return_success();
    // read_return_error();
    // read_return_zero();
    read_from_stdin();
    return 0;
}