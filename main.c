#include "shell_functions.h"

int main() {
    char buffer[1024];
    char test_path[1024];
    char cwd[1024];

    while(1) {
        display_prompt(cwd);
        read_input(buffer);

        char *buffer_copy = malloc(strlen(buffer) + 1);
        strcpy(buffer_copy, buffer);

        char *command = strtok(buffer_copy, " ");

        if (strcmp(buffer, "exit") == 0) {
            free(buffer_copy);
            break;
        }

        if (command != NULL && strcmp(command, "cd") == 0) {
            char *argument = strtok(NULL, " ");
            handle_cd(argument);
            free(buffer_copy);
            continue;
        }

        resolve_path(buffer, test_path);
        execute_command(buffer);
        free(buffer_copy);
    }
    return 0;
}

