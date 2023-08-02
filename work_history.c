#include "history_internal.h"

static t_list *get_max_input(t_list *head, int size)
{
    t_list *temp;
    int i;

    i = size - MAX_LOG_SIZE;
    temp = head;
    while (i-- >= 1)
        temp = temp->next;
    return (temp);
}

void work_history(int order, char *input)
{
    static t_list *head = NULL;
    static int  size = 0;

    if (order == INIT)
    {
        ft_read_history(open(HISTORY_FILE, O_RDONLY), &head, &size);
        if (size > MAX_LOG_SIZE)
            add_to_history(get_max_input(head, size));
        else if (head)
            add_to_history(head);
    }
    else if (order == UPDATE)
        update_history(&(head), input, &(size));
    else if (order == CLOSE)
        close_history(head, size, open(HISTORY_FILE, O_WRONLY | O_CREAT, 0644));
}

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