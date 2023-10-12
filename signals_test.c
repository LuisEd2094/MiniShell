#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void parent_sig_handler(int signum) {
    printf("Parent received signal %d\n", signum);
}

void child_sig_handler(int signum) {
    printf("Child received signal %d\n", signum);
}

int main() {
    pid_t child_pid;

    // Set up signal handler for parent
    signal(SIGINT, parent_sig_handler);

    // Fork
    child_pid = fork();

    if (child_pid == 0) {
        // Child process
        signal(SIGINT, child_sig_handler);

        // Rest of child process code
        sleep(5); // Simulate some work for the child
    } else if (child_pid > 0) {
        // Parent process

        // Rest of parent process code
        sleep(5); // Simulate some work for the parent
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}