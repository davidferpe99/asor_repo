#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {

    char *comm[3];

    if (argc != 2) {
        printf("Número invalido de argumentos.\nUso: ./system_execution\"<programm>\"\n");
        return -1;
    }
    comm[0] = strtok(argv[1], " ");
    comm[1] = strtok(NULL, " ");
    comm[2] = NULL;

    execvp(comm[0], comm);
    printf("El comando terminó su ejecución.\n");
    

    return 0;
}
