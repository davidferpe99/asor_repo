#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){
    printf ("Número máximo de enlaces: %li\n", pathconf("/", _PC_LINK_MAX));
    printf ("Tamaño máximo de ruta: %li\n", pathconf("/", _PC_PATH_MAX));
    printf ("Tamño máximo de nombre para ficheros: %li\n", pathconf("/", _PC_MAX_NAME));
    return 0;
}
