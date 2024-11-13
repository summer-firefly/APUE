#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main() {
    const char *message = "Hello World\n";
    ssize_t len = write(STDERR_FILENO, message, strlen(message));
    fprintf(stdout, "write %zd bytes\n", len);
    return 0;
}
