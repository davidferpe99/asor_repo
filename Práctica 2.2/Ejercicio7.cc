#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){

    

    mode_t mask = umask(027);

    int file = open("fichero2.txt", O_CREAT | O_RDONLY | O_TRUNC, 0777);
    


    return 1;
}
