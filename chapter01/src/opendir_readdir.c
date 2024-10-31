#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
void opendir_readdir_usage() {
    DIR *dir;
    struct dirent *ptr;
    dir = opendir("/");
    while (ptr = readdir(dir)) {
        printf("%s\n", ptr->d_name);
    }
    closedir(dir);
}
int main() {
    printf("opendir和readdir函数的使用\n");
    opendir_readdir_usage();
    return 0;
}