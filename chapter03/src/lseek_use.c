#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
void test01() {
    // 使用lseek获取当前文件偏移量
    int fd = open("./test.txt", O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        return;
    }
    write(fd, "nice", strlen("nice"));
    off_t off = lseek(fd, 0, SEEK_CUR);
    printf("写入nice之后,文件的偏移量为%ld\n", off);
    close(fd);
}
void test02() {
    // 使用lseek获取文件大小
    int fd = open("./test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }
    off_t off = lseek(fd, 0, SEEK_END);
    printf("文件的大小为%ld\n", off);
    close(fd);
}
void test03() {
    // 测试lseek能否对标准输入设置偏移量
    off_t off = lseek(STDIN_FILENO, 0, SEEK_CUR); // 尝试获取标准输入文件当前的偏移量
    printf("off=%ld\n", off);
    if (off == -1) {
        perror("lseek");
        printf("errno = %d\n", errno);
        if (errno == ESPIPE) {
            printf("errno被设置为ESPIPE\n");
        }
    }
}
int main() {
    // test01();
    // test02();
    test03();
    return 0;
}