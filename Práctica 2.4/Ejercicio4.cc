#include  <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char **argv){
    int fd;

    if (argc != 2){
        fprintf(stderr, "Número de argumentos incorrecto.\n Uso: ./Ejercicio4.o <fifo_file>\n");
        return -1;
    }

    if ((fd = open(argv[1], O_WRONLY)) < 0){
        perror("open");
        return -1;
    }

    write(fd, argv[1], strlen(argv[1]));

    close(fd);

    return 0;
}
