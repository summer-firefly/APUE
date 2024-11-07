#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // 在access与open之间(line 10),os-release内容可能会被修改,open之后read读到的就是被修改后的数据。检查操作与文件打开操作不是一个原子操作。
    if (access("/etc/os-release", F_OK) != -1) {
        // 文件存在，尝试打开
        int fd = open("/path/to/file", O_RDWR);
        if (fd == -1) {
            perror("open");
        }
        // 进行读写操作
        close(fd);
    }
    return 0;
}
