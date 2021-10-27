#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    time_t t = time(NULL);
    printf("Segundos en Epoch: %li\n", t);

    return 0;
}
