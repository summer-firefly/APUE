#include <unistd.h>
#define BUFFER_SIZE 4096
int main() {
    char buf[BUFFER_SIZE];
    ssize_t size;
    while ((size = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, size) == -1) {
            break;
        }
    }
    return 0;
}