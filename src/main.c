#include <history.h>


int main() {
    char* input;

    // Readline setup

    // Read previous history from a file
    work_history(INIT, NULL);
    int i = 0;

    // Main loop
    while (i++ < 3) {
        input = readline(">> "); // Prompt the user and read input
        if (!input) {
            // NULL input indicates EOF or an error (e.g., Ctrl+D)
            printf("\n");
            break;
        }

        if (input[0] != '\0') {
            // If the input is not empty, add it to the history
            work_history(UPDATE, input);
        }

        // Your processing logic here...
        printf("You entered: %s\n", input);

        free(input); // Free the memory allocated by readline
    }

    // Save history to a file before exiting
    work_history(CLOSE, NULL);


    return 0;
}