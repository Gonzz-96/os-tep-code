#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 128

char buff[BUFSIZE];

void check_pid(pid_t pid);
void first_child_procedure (int);
void second_child_procedure(int);

int main(int argc, char *argv[]) { 

    int file_des[2];
    pipe(file_des);
    
    int writer_fd = file_des[1];
    int reader_fd = file_des[0];

    pid_t first_child = fork();
    check_pid(first_child);
    if (first_child == 0) {
        close(reader_fd);
        first_child_procedure(writer_fd);
    }

    pid_t second_child = fork();
    check_pid(second_child);
    if (second_child == 0) {
        close(writer_fd);
        second_child_procedure(reader_fd);
    }

    waitpid(first_child,  NULL, 0); 
    waitpid(second_child, NULL, 0); 
    printf("parent: both children are done!\n");

    return 0;
}

void check_pid(pid_t pid) {
    if (pid < 0) {
        fprintf(stderr, "error creating child process\n");
        exit(1);
    } 
}

void first_child_procedure(int writer_fd) {
    strcpy(buff, "hello from first child!");
    printf("first child: writing to pipe!\n");
    write(writer_fd, buff, strlen(buff));
    close(writer_fd);
    exit(0);
}

void second_child_procedure(int reader_fd) {
    printf("second child: reading from pipe\n");
    read(reader_fd, buff, BUFSIZE);
    close(reader_fd);
    printf("second child: pipe says \"%s\"\n", buff);
    exit(0);
}
