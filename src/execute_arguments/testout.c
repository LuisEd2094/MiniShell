#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
int main(int argc, char **arv, char **env)
{
    char ** ls = (char **)malloc(sizeof(char *) * 4);
    ls[0] = "ls";
    ls[1] = NULL;
    ls[2] = "-la";
    ls[3] = NULL;


    execve("/usr/bin/ls", ls, env);
}*/
/*int file_descriptor = open("test3.txt asdads", O_RDONLY);

    if (file_descriptor == -1) {
        perror("minishell: test3.txt asdads");
        return 1;
    }*/
    /*
    int input_file = open("test.txt", O_RDONLY); // IF YOU NEED TO REAPLCE THE CONTENT LIKE IWTH ">"
    //int output_fd = open("test1.txt", O_WRONLY | O_CREAT | O_APPEND, 0644); // IF YOU NEED TO APPEND THE CONTENT LIKE WITH ">>"

    if (input_file == -1) {
        perror("open");
        return 1;
    }
    dup2(input_file, 1);/*
    output_fd = open("prueba.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (output_fd == -1) {
        perror("open");
        return 1;
    }

    printf("HOLA\n"),

    dup2(output_fd, 1);
    // Duplicate the file descriptor onto standard mini.input (0)
    dup2(file_descriptor, 0);*/

    /*char ** ls = (char **)malloc(sizeof(char *) * 2);
    ls[0] = "cat";
    ls[1] = NULL;


    execve("/usr/bin/cat", ls, env);*/


/*
    int pipe_fd[2];
    
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();
    
    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    
    if (child_pid == 0) { // Child process (cat)
        close(pipe_fd[1]);  // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
        
        char *cat_args[] = {"cat", "-e", NULL};
        execve("/usr/bin/cat", cat_args, NULL);
        
        perror("Execve failed");
        exit(EXIT_FAILURE);
    } else { // Parent process (ls)
        close(pipe_fd[0]);  // Close read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        
        // Print the information you want to pass to cat -e
        printf("This is the information that will be passed to cat -e\n");
        
        fflush(stdout); // Flush stdout before fork
        
        char *ls_args[] = {"ls", NULL};
        execve("/bin/ls", ls_args, NULL);
        
        perror("Execve failed");
        exit(EXIT_FAILURE);
    }*/
/*
    bool *has_;

    has_= (bool *)malloc(sizeof(bool) * 4);
    has_[0] = 0;
    has_[1] = 1;
    has_[2] = 0;
    has_[3] = NULL;


    for (int j = 0; j < 3; j++)
    {
        printf("Has pos [%i] has this value =  [%i]\n", j, has_[j]);
    }*/
    // Read previous history from a file

    //printf("%s", "hola\"");



/*
int main() {
    // Save the original stdout file descriptor
    int original_stdout = dup(STDOUT_FILENO);

    // Redirect stdout to your first file
    int file1 = open("output1.txt", O_WRONLY | O_CREAT, 0666);
    if (file1 != -1) {
        // Redirect stdout to the first output file
        dup2(file1, STDOUT_FILENO);
        close(file1);


        // Perform your first print operation using printf
        write(1, "First File\n", strlen("First File\n"));
        // Restore stdout to the original file descriptor
        dup2(original_stdout, STDOUT_FILENO);

        // Print a message to the terminal
        write(1, "TERMINAL 1\n", strlen("TERMINAL 1\n"));

        // Close the first output file
    } else {
        perror("Error opening first file");
    }


    // Redirect stdout to your second file
    int file2 = open("output2.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (file2 != -1) {
        // Redirect stdout to the second output file
        dup2(file2, STDOUT_FILENO);

        // Perform your second print operation using printf
        write(1, "Second File\n", strlen("Second File\n"));

        // Clean up: Close the second output file
        close(file2);
    } else {
        perror("Error opening second file");
    }
    dup2(original_stdout, STDOUT_FILENO);

    // Perform your third print operation using printf
    write(1, "TERMINAL 2\n", strlen("TERMINAL 2\n"));
    // Clean up: Close the original stdout
    close(original_stdout);

    return 0;
}*/