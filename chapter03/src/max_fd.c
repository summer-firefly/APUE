#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int maxfd_by_sysconf() {
    return sysconf(_SC_OPEN_MAX);
}
int maxfd_by_test() {
    int max_fd = 0;
    while (1) {
        if (open("test.txt", O_RDONLY) == -1) {
            break;
        }
        max_fd++;
    }
    return max_fd;
}
int main() {
    printf("test1 : 最大文件描述符 %d\n", maxfd_by_sysconf());
    printf("test2 : 最大文件描述符 %d\n", maxfd_by_test());
    return 0;
}