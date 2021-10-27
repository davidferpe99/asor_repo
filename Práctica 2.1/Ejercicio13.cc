#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int main(){
    struct timeval t;
    int time1 = gettimeofday(&t, NULL);
    int inicio = t.tv_usec;

    
    for (int i = 0; i < 1000000; i++){

    }

    int time2 = gettimeofday(&t, NULL);
    int fin = t.tv_usec;

    printf("Tiempo total: %i (ms)", fin - inicio);

    return 1;
}
