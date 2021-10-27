#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int main() {
    time_t t = time(NULL);
    struct tm *info = localtime(&t);

    int ano = info->tm_year;

    printf("Año: %i\n", 1900 + ano);
    return 1;
}
