#include "shell_functions.h"

int main() {
    char buffer[1024]; // store the command
    char test_path[1024]; // find the executable in the files
    char cwd[1024]; // store the path of the command

    while(1) {
        display_prompt(cwd); // print the prompt
        read_input(buffer); // read the user's command

        char *buffer_copy = malloc(strlen(buffer) + 1); // copy the buffer 
        strcpy(buffer_copy, buffer); // stock it

        char *command = strtok(buffer_copy, " "); // cut the command

        if (strcmp(buffer, "exit") == 0) { // if exit is use 
            free(buffer_copy); // free the space in buffer copy
            break;
        }

        if (command != NULL && strcmp(command, "cd") == 0) { // is cd is use
            char *argument = strtok(NULL, " "); // check the rest of the command for a destination folder
            handle_cd(argument); // change the folder
            free(buffer_copy); // free the space in buffer copy
            continue;
        }

        resolve_path(buffer, test_path); // find an absolute path
        execute_command(buffer); // use the command in a child
        free(buffer_copy); // free the space in buffer copy
    }
    return 0;
}

