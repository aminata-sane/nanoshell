#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Function declarations
void display_prompt(char *cwd);
void read_input(char *buffer);
void handle_cd(char *argument);
void resolve_path(char *buffer, char *chemin_test);
void execute_command(char *buffer);