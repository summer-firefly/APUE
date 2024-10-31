#include <stdio.h>
#include <signal.h>
void SIGINT_HANDLE(int sig) {
    printf("收到 SIGINT 信号\n# ");
    fflush(stdout);
}
void SIGQUIT_HANDLE(int sig) {
    printf("收到 SIGQUIT 信号\n# ");
    fflush(stdout);
}
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
    signal(SIGINT, SIGINT_HANDLE);
    signal(SIGQUIT, SIGQUIT_HANDLE);
    shell();
    return 0;
}