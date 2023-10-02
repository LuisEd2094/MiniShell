#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_pipe(char ***commands, int num_pipes, int i, char *env[]) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("Error in fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        if (i == 0)
            execve("/usr/bin/ls", commands[i], env);
        else
            execve("/usr/bin/ps", commands[i], env);
        printf("I am leaving\n");
        // ...
        exit(EXIT_SUCCESS); // Terminate child process
    } else {
        // Parent process
        if (i < num_pipes) {
            wait(&status); // Wait for child process to finish
            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                printf("Child process exited with status %d\n", exit_status);
            }
        }
    }
}

int main(int argc, char *argv[], char *env[]) {
    char *cmd1[] = {"ls", NULL};
    char *cmd2[] = {"ps", NULL, NULL};
    char **commands[] = {cmd1, cmd2};

    int num_pipes = 2;

    for (int i = 0; i < num_pipes; i++) {
        execute_pipe(commands, num_pipes, i, env);
    }

    return 0;
}