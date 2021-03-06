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

    int fd2 = dup2(fd, 1);
    dup2(fd2,fd);

    return 1;
}
