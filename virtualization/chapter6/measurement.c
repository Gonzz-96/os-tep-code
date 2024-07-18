#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

#define NCALLS 300

int main(int argc, char *argv[]) {

    char empty_buff[1];
    struct timeval init;
    struct timeval end;

    gettimeofday(&init, NULL);
    
    for (int i = 0; i < NCALLS; i++) {
        read(STDIN_FILENO, empty_buff, 0);    
    }

    gettimeofday(&end, NULL);

    int total_time = end.tv_sec - init.tv_sec;
    printf("Number of syscalls: %d\n", NCALLS);
    printf("Total time: %d\n", total_time);
    printf("Time per syscall: %.5f\n", (float)total_time / (float) NCALLS);

    return 0;
}

