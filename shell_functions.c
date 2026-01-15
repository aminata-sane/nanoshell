#include "shell_functions.h"

// Function implementations
void display_prompt(char *cwd) {
    getcwd(cwd, sizeof(cwd));
    printf("%s ?>", cwd);
}

void read_input(char *buffer) {
    fgets(buffer, 1024, stdin);
    int len = strlen(buffer);
    if (len > 0) buffer[len - 1] = '\0';
}

void handle_cd(char *argument) {
    if (argument != NULL) {
        if (chdir(argument) != 0) {
            perror("Erreur cd");
        }
    }
}

void resolve_path(char *buffer, char *chemin_test) {
    if (buffer[0] != '/') {
        char *raw_path = getenv("PATH");
        int path_len = strlen(raw_path);
        char *path_copy = malloc(path_len + 1);
        strcpy(path_copy, raw_path);
        char *dossier = strtok(path_copy, ":");

        while (dossier != NULL) {
            strcpy(chemin_test, dossier);
            strcat(chemin_test, "/");
            strcat(chemin_test, buffer);

            if (access(chemin_test, X_OK) == 0) {
                strcpy(buffer, chemin_test);
                break;
            }
            dossier = strtok(NULL, ":");
        }
        free(path_copy);
    }
}

void execute_command(char *buffer) {
    pid_t pid = fork();

    if (pid == 0) {
        char *args[2];
        args[0] = buffer;
        args[1] = NULL;
        execve(args[0], args, NULL);
        perror("Erreur");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }
}