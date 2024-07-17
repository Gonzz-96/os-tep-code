#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "error forking process\n");
        return 1;
    } else if (pid == 0) {
        printf("child: hello\n");
        // hypothesis: calling 'wait' in the child process, WITHOUT forking another process,
        // will produce a -1 value, as there's no child to wait
        pid_t child_pid = wait(NULL);
        printf("wait in child process: %d\n", child_pid);
    } else {
        // hypothesis: waitpid expects a pid to be waited. This can be useful when the parent
        // have multiple children. If the pid doesn't exist or it's not a child of the parent,
        // -1 is returned as it's considered an error by the OS
        pid_t terminated_pid = waitpid(pid , NULL, 0);
        printf("child id: %d, terminated process id: %d\n", pid, terminated_pid);
        printf("parent: goodbye\n");
    }

    return 0;
}

