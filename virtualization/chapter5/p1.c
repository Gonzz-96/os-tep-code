#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello (parent pid:%d)\n", (int) getpid());
    // the child process starts its execution with the fork()
    // call, so anything previous to that call is ignored
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process (new process)
        printf("child (pid:%d)\n", (int) getpid());
    } else {
        // parent goes down this path (main)
        printf("parent of %d (parent pid:%d)\n", rc, (int) getpid());
    }
    return 0;
}

