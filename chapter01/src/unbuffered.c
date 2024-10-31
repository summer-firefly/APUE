#include <unistd.h>
int main() {
    char buf[1024];
    int n;
    while ((n = read(0, buf, 1024)) > 0) {
        write(1, buf, n);
    }
    return 0;
}