#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main( int argc, char **argv){
    if (argc < 2){
        printf("Error: Falta la ruta del archivo como parámetro.\n");
        return -1;
    }

    int fd = open(argv[1], O_CREAT | O_RDWR, 00777);
    if (fd == -1){
        printf("Error: No ha sido posible abrir/crear el archivo.\n");
        return -1;
    }

    int fd3 = dup2(fd,2);
    int fd2 = dup2(fd, 1);

    char *s;
    if (setuid(0) == -1){
        perror(s);
    }

    dup2(fd2,fd);
    dup2(fd3,fd);
    return 1;
}

//ls>dirlist>&1: Redirecciona la salida estandar a dirlist y luego la salida de errores a la 1 que corresponde a dirlist, en conclusión, ambas salidas se van a ver en dirlist.
//ls 2>&1>dirlist: Redirecciona lña salida de error a la salida estandar y la salida estandar a dirlist, por lo que los errores se van a ver por pantalla y la salida normal en el fichero dirlist.
