#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[], char *env[]) {

    char line[1024 * 4] = {0};
    char *argv [] = {"ls", "-la", NULL};
    char *env [] = {NULL};
    int pid = -1;

    while (true) {
        printf("?> ");
        handle_input(line);
        pid = fork();
        printf("pid: %d\n", pid);
        waitpid(pid, NULL, 0);
        printf("zerty");
        exit(-1);
    }
    return 0;
}

