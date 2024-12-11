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
    int dirfd = open("/usr/include", __O_DIRECTORY);
    if (dirfd == -1) {
        perror("open");
        return -1;
    }
    // int faccessat(int dirfd, const char *pathname, int mode, int flags);
    if (faccessat(dirfd, "./stdio.h", F_OK, 0) == 0) {
        printf("file exists\n");
    } else {
        return 0;
    }
    if (faccessat(dirfd, "./stdio.h", R_OK, 0) == 0) {
        printf("The process has read permission for files\n");
    }
    if (faccessat(dirfd, "./stdio.h", W_OK, 0) == 0) {
        printf("The process has write permission for files\n");
    }
    if (faccessat(dirfd, "./stdio.h", X_OK, 0) == 0) {
        printf("The process has execute permission for files\n");
    }
    return 0;
}