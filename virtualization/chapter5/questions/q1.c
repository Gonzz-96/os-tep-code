#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;

    int pid = fork();

    if (pid < 0) {
        fprintf(stderr, "error forking a process\n");
        return 1;
    } else if (pid == 0) {
        // hypothesis: since a forked process is a copy of the parent process but with a
        // different address space, the 'x' variable won't have any change in the parent
        // process, and the modified value will be in the child address space.
        x = 20;
        printf("Child process (%d): %d\n", (int)getpid(),  x);
    } else {
        wait(NULL);
        // hypothesis: parent's address space is not modified by the child. Any changes
        // is made in an isolated environment.
        x = 40;
        printf("Parent process (%d): %d\n", (int)getpid(),  x);
    }

    return 0;
}

