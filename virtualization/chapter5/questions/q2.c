#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int fd = open("output", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    int pid = fork();

    if (pid < 0) {
        fprintf(stderr, "error forking process\n");
        return 1;
    } else if (pid == 0) {
        char *str = "child string\n";
        write(fd, str, strlen(str));
    } else {
        // since the address space is copied in the image of the child, it receives
        // a copy of the file descriptor, meaning that both processes can write to
        // the same file. However, there's a chance of getting a race condition. The
        // 'wait' system call solves that issue for this program, buy a synchronization
        // mechanism is recommended in other cases.
        wait(NULL);
        char *str = "parent string\n";
        write(fd, str, strlen(str));
    }

    close(fd);

    return 0;
}

