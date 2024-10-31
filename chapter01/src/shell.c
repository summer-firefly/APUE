#include <stdio.h>
void shell() {
    char command[1024];
    while (1) {
        printf("# ");
        fflush(stdout);
        fgets(command, 1024, stdin);
        if (!strcmp(command, "exit\n")) {
            break;
        }
        int pid = fork();
        if (pid == 0) {
            execl("/bin/sh", "sh", "-c", command, NULL);
        }
        waitpid(pid, NULL, 0);
    }
}
int main() {
    shell();
    return 0;
}