#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <dirent.h>
int main() {
    int fd = open("/usr/include/stdio.h", O_RDWR | O_APPEND);
    if (fd < 0) {
        perror("open"); // open: Permission denied
        return 0;
    }
    ssize_t len = write(fd, "append", 6);
    if (len < 0) {
        perror("write");
        return 0;
    }
    close(fd);
    return 0;
}