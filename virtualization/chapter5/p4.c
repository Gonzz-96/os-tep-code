#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process: redirects standard output to a file
        close(STDOUT_FILENO);
        open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        //
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc"
        myargs[1] = strdup("p4.c"); // arg: input file
        myargs[2] = NULL;           // mark end of array
        execvp(myargs[0], myargs);
    } else {
        wait(NULL);
    }
    return 0;
}

