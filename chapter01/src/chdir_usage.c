#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
void listCurrentDirAllEntry() {
    DIR *dir;
    struct dirent *ptr;
    dir = opendir(".");
    while (ptr = readdir(dir)) {
        printf("%s\n", ptr->d_name);
    }
    closedir(dir);
    
}
int main() {
    chdir("/");
    listCurrentDirAllEntry();
    chdir("/usr/include");
    listCurrentDirAllEntry();
    return 0;
}