#include "shell.h"




int main(int ac, char **av){

    (void)ac;
    int status;
    if (fork() == 0)
        execvp(av[1], av+1);

    wait(&status);

    return EXIT_SUCCESS;
}