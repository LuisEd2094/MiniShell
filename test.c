#include <stdio.h>
#include <unistd.h>
#include "./includes/libft.h"

int main() {


    int fd = open("test.txt", O_RDONLY);
    int std_fd = dup2(fd, STDIN_FILENO);

    if (isatty(STDIN_FILENO)) {
        printf("Interactive session detected. You can input data:\n");
        char* terminal_name = ttyname(STDIN_FILENO);
        if (terminal_name) {
            printf("Terminal name: %s\n", terminal_name);
        }
        
        // Read input interactively using fgets or similar
        // ...
    } else {
        write(1, "Not an interactive session.\n", strlen("Not an interactive session.\n"));
    }

    return 0;
}

