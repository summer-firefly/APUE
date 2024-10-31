#include <stdio.h>
int main() {
    char buf[1024];
    while (fgets(buf, 1024, stdin)) {
        fprintf(stdout, "%s", buf);
    }
    return 0;
}