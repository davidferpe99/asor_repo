#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int main() {
    time_t t = time(NULL);
    struct tm *info = localtime(&t);


    char fecha[100];
    strftime(fecha, 100, "%A, %d de %B de %Y, %H:%M", info);

    printf(fecha);
    return 1;
}
