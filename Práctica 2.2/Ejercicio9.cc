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

    printf("MAJOR: %li\n", (long) major(buff.st_dev));
    printf("MINOR: %li\n", (long) minor(buff.st_dev));

    printf ("I-NODE: %li\n", buff.st_ino);

    mode_t mode = buff.st_mode;

    if (S_SLINK(mode)){
        printf("%s es un enlace simbólico.\n", argv[1]);
    }
    else if (S_ISREG(mode)){
        printf("%s es un archivo.\n", argv[1]);
    }
     else if (S_ISDIR(mode)){
        printf("%s es un directorio.\n", argv[1]);
    }


    time_t t = buff.st_ctime;

    struct tm *tm1 = localtime(&t);

    printf("Último acceso (st_ctime): %d:%d\n", tm1->tm_hour, tm1->tm_min);

    time_t t2 = buff-st_mtime;

    struct tm *tm2 = localtime(&t2);

    printf("Último acceso (st_mtime): %d:%d\n", tm2->tm_hour, tm2->tm_min);


    return 0;
}
//st_mtime muestra la fecha de la ultima modificación del archivo
//st_ctime muestra la ulñtima modificación ya sea de permisos, del archivo, de nombre, etc.
