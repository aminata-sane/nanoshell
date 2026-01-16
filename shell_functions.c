#include "shell_functions.h"

// Function implementations
void display_prompt(char *cwd) { // manage the path
    getcwd(cwd, sizeof(cwd)); // find the path the user in on
    printf("%s ?>", cwd); // print the path
}

void read_input(char *buffer) { // put the user's command in buffer and cancel \n
    fgets(buffer, 1024, stdin); // read the command and stock it in the buffer
    int len = strlen(buffer); // take count of the height of the command
    if (len > 0) buffer[len - 1] = '\0'; // replace the \n
}

void handle_cd(char *argument) { // manage cd
    if (argument != NULL) { // check if there is something
        if (chdir(argument) != 0) { // change the current repository
            perror("Error cd"); // print an error if chdir fail
        }
    }
}

void resolve_path(char *buffer, char *test_path) { // check if the command is correct
    if (buffer[0] != '/') { // check if it's a absolute path ( C:\msys64\mingw64\bin ) or a relative path (nanoshell.exe)
        char *raw_path = getenv("PATH"); // take count of the path environment variable
        int path_len = strlen(raw_path);
        char *path_copy = malloc(path_len + 1);
        strcpy(path_copy, raw_path); // Copy path for strtok
        char *folder = strtok(path_copy, ":"); // Separate each folder from path

        while (folder != NULL) { // check the differents folders
            strcpy(test_path, folder);
            strcat(test_path, "/");
            strcat(test_path, buffer);

            if (access(test_path, X_OK) == 0) { // test if it's executable
                strcpy(buffer, test_path); // replace the buffer path with this new one
                break;
            }
            folder = strtok(NULL, ":"); // change of folder
        }
        free(path_copy);
    }
}

void execute_command(char *buffer) { // execute the command with a child
    pid_t pid = fork(); // create a child

    if (pid == 0) { // in the child
        char *args[2]; // create a chart
        args[0] = buffer; // contain the all path of the command
        args[1] = NULL; // read the chart
        execve(args[0], args, NULL); // execute the command
        perror("Error"); // if execve fail, it print an error
        exit(1); // end the child
    } else { // the parent execute that in the time
        waitpid(pid, NULL, 0); // the parent shell waits that the child's command ends
    }
}