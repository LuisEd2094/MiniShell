#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
       #include <errno.h>


int main() {


    int fd[2];

    int fd_file = open("infile", O_RDONLY);
    int fd_out = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int og_out = dup(STDOUT_FILENO);

    dup2(fd_out, STDOUT_FILENO);
    close(fd_out);



    dup2(fd_file, STDIN_FILENO);
    close(fd_file);
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        close(fd[0]); // Close the read end of the pipe

        // Redirect standard output to the write end of the pipe
        if (isatty(STDOUT_FILENO))
            dup2(fd[1], STDOUT_FILENO);
        close(fd[1]); // Close the write end of the pipe in the child

        char *args[] = {"/bin/ls", NULL};
        execve("/bin/ls", args, NULL);

        // If execve() fails, the following code will be executed
        perror("execve");
        exit(errno); // Use _exit to avoid flushing stdio buffers
    } else if (pid > 0) {
        int status;
        wait(&status);
        // Parent process
        close(fd[1]); // Close the write end of the pipe

        char buffer[100];
        int bytesRead;//

        if (!isatty(STDOUT_FILENO))
            dup2(og_out, STDOUT_FILENO);
        if (isatty(STDIN_FILENO))
            dup2(fd[0], STDIN_FILENO);

        printf("status [%i]\n", status);
        //read(STDIN_FILENO, buffer, sizeof(buffer));
        //write (STDOUT_FILENO, buffer, strlen(buffer));
        char *args[] = {"/bin/cat", "-e",NULL};
        execve("/bin/cat", args, NULL);

        close(fd[0]); // Close the read end of the pipe in the parent
    } else {
        perror("fork");
        return 1;
    }

    return 0;}/*


    int fd[2];
    //int fd_file = open("infile", O_RDONLY);
    //int fd_out = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0644);


    int og_out = dup(STDOUT_FILENO);
    //dup2(fd_out, STDOUT_FILENO);
    //close(fd_out);
    //dup2(fd_file, STDIN_FILENO);
    //close(fd_file);
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        close(fd[0]); // Close the read end of the pipe

        //char buffer[100] = "Hello from child!";
        //if (isatty(STDIN_FILENO))
        char *args[] = {"cat", NULL};
        
        //f (isatty(STDOUT_FILENO))
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]); // Close the write end of the pipe in the child
        execve("/bin/cat", args, NULL);

        //write(fd[1], buffer, sizeof(buffer)); // Write to the pipe

    } else if (pid > 0) {
        // Parent process
        close(fd[1]); // Close the write end of the pipe

        char buffer[100];
        int bytesRead;;
        //IF last parent
        //if (!isatty(STDOUT_FILENO))
          //  dup2(og_out, STDOUT_FILENO);
        //dup2(fd[0], STDIN_FILENO);
       // if (!isatty(STDERR_FILENO))

    
        bytesRead = read(fd[0], buffer, sizeof(buffer));

        printf("Parent read %d bytes: %.*s\n", bytesRead, bytesRead, buffer);

        close(fd[0]); // Close the read end of the pipe in the parent
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}*/
/*

    int fd_file = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
    dup2(fd_file, STDOUT_FILENO);
    close(fd_file);


    if (pid == 0) {
        // Child process
        char *args[] = {"ls", NULL}; // Example command (list files in current directory)
        if(!isatty(fd))
            write(STDOUT_FILENO,"I am  NOT pointng to terminal\n", strlen("I am  NOT pointng to terminal\n"));
        execve("/bin/ls", args, NULL);

        // If execve() fails, the following code will be executed
        perror("execve");
        printf("HELLO\n");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status;
        wait (&status);
        // Parent process
        printf("Parent process continues running\n");
        // Additional code for parent process
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}*/