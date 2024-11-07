#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
void test01() {
    //使用lseek获取当前文件偏移量
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
int main() {
    test01();
    return 0;
}