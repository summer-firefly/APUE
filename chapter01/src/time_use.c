#include <time.h>
#include <stdio.h>
int main() {
    time_t timeStamp = time(NULL);
    printf("时间戳是 : %ld\n", timeStamp);
    return 0;
}
