#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){

    const char path[] = "/home/ASOR/Práctica2.2/fichero.txt";

   

    int df = open(path, O_CREAT, 0645);



    return 1;
}
