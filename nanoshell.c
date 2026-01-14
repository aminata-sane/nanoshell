#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char buffer[1024];

    while(1) { // La boucle infinie while(1).
        printf("?>"); // L'affichage du prompt ?>.
        fgets(buffer,1024,stdin); // La lecture avec fgets.
        int len = strlen (buffer); 
        buffer[len - 1] = '\0'; // Le "nettoyage" du retour à la ligne avec len - 1.

        if (strcmp (buffer, "exit") == 0) { // La condition de sortie propre avec strcmp et break.
            break;
        }

        pid_t pid = fork();

        if (pid == 0) {
            char *args [2];
            args[0]=buffer; 
            args[1]= NULL;
            execve(args[0], args, NULL);
            perror("Erreur");
            return(0);
        }
        
        else{
            wait (NULL);
        }
    }
    return (0);
}