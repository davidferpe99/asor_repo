#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){
    printf ("Longitud máxima de los argumentos: %li\n", pathconf("/", _PC_LINK_MAX));
    printf ("Número máximo de hijos: %li\n", pathconf("/", _PC_PATH_MAX));
    printf ("Número máximo de ficheros: %li\n", pathconf("/", _PC_MAX_INPUT));
    return 0;
}
