#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int pid = fork();

    if (pid < 0) {
        fprintf(stderr, "error forking process\n");
        return 1;
    } else if (pid == 0) {
        // if the child closes the STOUD file descriptor, it is closed only for
        // the child. This file descriptor is still open in the parent process
        // My hypothesis is that the copy of the parent process includes the fd
        // of the stdouf, hence the copy is closed, and the original is still open.
        close(STDOUT_FILENO);
        printf("child: hello\n");
    } else {
        wait(NULL);
        printf("parent: goodbye\n");
    }

    return 0;
}

