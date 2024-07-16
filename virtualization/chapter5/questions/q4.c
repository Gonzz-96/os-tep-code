#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int equals(char *left, char *right) {
    return strcmp(left, right) == 0;
}

void run_exec_variant(char *exec_variant, char *envp[]) {
    if (equals(exec_variant, "execl"))  { 
        // the 'l' family of the 'exec' system calls expects a 'list'
        // of arguments by expecting a varargs parameter.
        execl ("/bin/ls", "ls", NULL); 

    } else if (equals(exec_variant, "execle")) { 
        // the 'e' variants expect an array containing the environment variables.
        // However, we need to add a NULL (0) parameter to let know the function
        // that the next argument is the env vars array.
        execle("/bin/ls", "ls", NULL, envp);

    } else if (equals(exec_variant, "execlp")) {
        // the 'p' looks for the file in all the directories included in
        // the $PATH environment variable, so there's no need for absolute paths
        execlp("ls", "ls", NULL);    

    } else if (equals(exec_variant, "execv")) {
        // the 'v' varians expects an array of arguments instead of a list.
        // This array must be null-ending
        char *args[] = { "ls", NULL };
        execv("/bin/ls", args);

    } else if(equals(exec_variant, "execvp")) {
        char *args[] = { "ls", NULL };
        execvp("ls", args);

    } else if(equals(exec_variant, "execvpe")) {
        char *args[] = { "ls", NULL };
        execvpe("ls", args, envp);

    } else {
        fprintf(stderr, "no exec variant: %s\n", exec_variant);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    if (argc < 2) {
        fprintf(stderr, "missing argument\nusage: ./a.out <exec_variant>\n");
        fprintf(stderr, "available variants:\n\texecl\n\texecle\n\texeclp");
        fprintf(stderr, "\n\texecv\n\texecvp\n\texecvpe\n");
        return 1;
    }

    int pid = fork();

    if (pid < 0) {
        fprintf(stderr, "error forking process\n");
        return 2;
    } else if (pid == 0) {
        run_exec_variant(argv[1], envp);
    } else {
        wait(NULL);
    }

    return 0;
}


