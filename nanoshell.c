#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    char buffer[1024];
    char chemin_test[1024];
    char cwd [1024];

    while(1) { // La boucle infinie while(1).

        getcwd(cwd, sizeof(cwd));
        printf("%s ?>", cwd); // L'affichage du prompt cwd.
        fgets(buffer,1024,stdin); // La lecture avec fgets.
        int len = strlen (buffer); 
        buffer[len - 1] = '\0'; // Le "nettoyage" du retour à la ligne avec len - 1.

        // copie de mon buffer
        char *buffer_copy = malloc(strlen(buffer) + 1);
        strcpy(buffer_copy, buffer);

        // Ici on travaille sur la copie de mon buffer pour le test "cd"
        char *commande = strtok(buffer_copy, " ");

        if (strcmp (buffer, "exit") == 0) { // La condition de sortie propre avec strcmp et break.
            free(buffer_copy);
            break;
        }

        if (commande != NULL && strcmp(commande, "cd") == 0) {
            char *argument = strtok (NULL, " "); 
            if (argument != NULL) {
                if (chdir (argument) != 0) {
                    perror ("Erreur cd"); 
                }
            }
            free(buffer_copy);
            continue; 
        }

        pid_t pid = fork();

        if (pid == 0) {

            free(buffer_copy);

            if (buffer[0] != '/') {
                char *raw_path = getenv("PATH");
                int path_len = strlen (raw_path);
                char *path_copy = malloc(path_len + 1);
                strcpy(path_copy, raw_path);
                char *dossier = strtok(path_copy, ":");
                

                while (dossier != NULL) {
                        strcpy(chemin_test, dossier);
                        strcat(chemin_test, "/");
                        strcat(chemin_test, buffer);
                        
                        if (access(chemin_test, X_OK) == 0) {
                            strcpy (buffer, chemin_test);
                            break; 
                        }
                        dossier = strtok(NULL, ":");
                        
                }
                free(path_copy);
             }

            char *args [2];
            args[0]=buffer; 
            args[1]= NULL;
            execve(args[0], args, NULL);
            perror("Erreur");
            return(0);
        }

        else{
            waitpid(pid, NULL, 0);
            free(buffer_copy);
        }
    }
    return (0);
}