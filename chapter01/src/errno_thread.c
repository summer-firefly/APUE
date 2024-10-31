#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
static void *enter(void *args) {
    open("notExists.txt", O_RDONLY);
    while (1) {
        printf("sub  thread : errno = %d\n", errno);
        sleep(1);
    }
    return NULL;
}
int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, enter, NULL);
    while (1) {
        printf("main thread : errno = %d\n", errno);
        sleep(1);
    }
    return 0;
}