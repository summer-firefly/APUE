#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
void empty_hole_test1() {
    struct stat st;
    int fd;
    off_t off;
    fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }
    fstat(fd, &st);
    printf("打开的文件大小为%ld\n", st.st_size);
    off = lseek(fd, 0, SEEK_CUR);
    printf("目前文件偏移量为%ld\n", off);
    write(fd, "hello", 5);
    off = lseek(fd, 0, SEEK_CUR);
    printf("写入'hello'之后文件偏移量为%ld\n", off);
    off = lseek(fd, 5, SEEK_END);
    printf("调整文件偏移量为%ld,在'hello'之后产生了一些文件空洞\n", off);
    write(fd, "world", 5);
    printf("写入'world'\n");
    fstat(fd, &st);
    printf("'hello'+'空洞'+'world'的大小为%ld\n", st.st_size);
    if (st.st_size == 10) {
        printf("文件空洞不占据磁盘空间\n");
    } else {
        printf("文件空洞占据磁盘空间\n");
    }
    close(fd);
}
void read_content() {
    // test.txt文件中包含"空洞",逐个字节读取test.txt中的文件内容
    int fd;
    fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }
    while (1) {
        char buf[1];
        int ret = read(fd, buf, 1);
        if (ret == -1) {
            perror("read");
            break;
        }
        if (ret == 0) {
            printf("文件读取完毕\n");
            break;
        }
        printf("%d\n", buf[0]);
    }
    close(fd);
}
void creat_big_file(size_t size) {
    // 利用"文件空洞"创建一个size大小的文件
    int fd;
    fd = open("big_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }
    lseek(fd, size - 1, SEEK_END);
    write(fd, " ", 1);
    close(fd);
}
int main() {
    empty_hole_test1();
    read_content();
    creat_big_file(1024 * 1024 * 1024);
    return 0;
}