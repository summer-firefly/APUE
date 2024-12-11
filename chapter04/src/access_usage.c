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
    int ret = -1;
    const char *fileName = "/usr/include/stdio.h";
    ret = access(fileName, F_OK);
    if (ret) {
        printf("file %s not exists\n", fileName);
        return -1;
    }
    ret = access(fileName, R_OK);
    if (!ret) {
        printf("The current process has read permission on the file %s\n", fileName);
    }
    ret = access(fileName, W_OK);
    if (!ret) {
        printf("The current process has write permission on the file %s\n", fileName);
    }
    ret = access(fileName, X_OK);
    if (!ret) {
        printf("The current process has execute permission on the file %s\n", fileName);
    }
    return 0;
}