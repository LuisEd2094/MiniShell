#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_pipe(char **commands[], int num_pipes) {
    int pipes[num_pipes - 1][2];  // Crea un array de tuberías

    for (int i = 0; i < num_pipes - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Error en pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_pipes; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Error en fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Proceso hijo

            // Redirige entrada desde la tubería anterior (excepto para el primer comando)
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]);
            }

            // Redirige salida a la tubería actual (excepto para el último comando)
            if (i < num_pipes - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][1]);
            }

            // Cierra todas las otras tuberías en este proceso hijo
            for (int j = 0; j < num_pipes - 1; j++) {
                if (j != i - 1) {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
            }

            execvp(commands[i][0], commands[i]);  // Ejecuta el comando
            perror("Error en execvp");
            exit(EXIT_FAILURE);
        }
    }

    // Cierra todas las tuberías en el proceso padre
    for (int i = 0; i < num_pipes - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Espera a que todos los procesos hijos terminen
    for (int i = 0; i < num_pipes; i++) {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    char *command1[] = {"echo", "valor_de_hola", NULL};
    char *command2[] = {"cat", "text.txt", NULL};
    char *command3[] = {"ls", "-la", NULL};

    char **commands[] = {command1, command2, command3};
    int num_pipes = sizeof(commands) / sizeof(commands[0]);

    execute_pipe(commands, num_pipes);

    return 0;
}
