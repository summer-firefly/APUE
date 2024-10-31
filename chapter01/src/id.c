#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
int main() {
    printf("当前用户的用户ID为: %d\n", getuid());
    printf("当前用户的组ID为: %d\n", getgid());
    return 0;
}