#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char **argv){

    if (argc < 2){
        printf("Error: Falta la ruta del archivo en los parámetros del programa.\n");
        return -1;
    }

    struct stat buff;

    int statint = stat(argv[1], &buff);

    if (statint = -1){
        printf("Error: No existe el directorio.\n");
        return -1;
    }

    char* hard = malloc(sizeof(char)*(5 + strlen(argv[1])));
    char* sym = malloc(sizeof(char)*(5 + strlen(argv[1])));
    strcpy(hard, argv[1]);
    strcpy(sym, argv[1]);

    printf("Hard: %s\n", hard);
    printf("Sym: %s\n", sym);

    mode_t mode = buff-st_mode;

    if (S_ISREG(mode)){
        printf("%s es un archivo ordinario.\n", argv[1]);

        if (link(argv[1], hard) == -1){
            printf("Error: No es posible crear el enlace rígido.\n");
        }
        else{
            printf("Seha creado el enlace rígido.\n");
        }

        if (link(argv[1], sym) == -1){
            printf("Error: No es posible crear el enlace simbólico.\n");
        }
        else{
            printf("Seha creado el enlace simbólico.\n");
        }

    }
    else{

        printf("Error: La ruta introducida no se trata de un fichero.\n");
    }





    return 0;
}
