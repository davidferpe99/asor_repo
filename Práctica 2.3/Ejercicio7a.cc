#include <stdio.h> 
#include <stdlib.h> 
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Número invalido de argumentos.\nUso: ./system_execution\"<programm>\"\n");
        return -1;
    }
    system(argv[1]);
    printf("El comando terminó su ejecución.\n");

    return 0;
}
