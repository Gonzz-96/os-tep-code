#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int pid = fork();

    if (pid < 0) {
        fprintf(stderr, "error forking process\n");
        return 1;
    } else if (pid == 0) {
        printf("child: hello\n");
    } else {
        sleep(1);
        printf("parent: goodbye\n");
    }

    return 0;
}

