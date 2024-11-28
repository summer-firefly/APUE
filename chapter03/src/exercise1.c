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
int my_dup2(int oldfd, int newfd) {
    if (oldfd == newfd) {
        return 0;
    }
    if (newfd < 0) {
        fprintf(stderr, "newfd error!\n");
        return -1;
    }
    close(newfd);
    int index = 0;
    int *tempfds = (int *)malloc(sizeof(int) * (newfd + 1));
    memset(tempfds, 0, sizeof(int) * (newfd + 1));
    int fd = dup(oldfd);
    while (fd != -1 && fd != newfd) {
        tempfds[index++] = fd;
        fd = dup(oldfd);
    }
    for (int i = 0; i < index; i++) {
        close(tempfds[i]);
    }
    free(tempfds);
    return fd != -1;
}
int main() {
    my_dup2(STDOUT_FILENO, 55);
    printf("pid=%d\n", getpid());
    getchar();
    return 0;
}