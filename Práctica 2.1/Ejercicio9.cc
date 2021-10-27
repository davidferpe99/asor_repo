#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){

    printf("UID real: %d\n", getuid());
    printf("UID efectivo: %d\n", geteuid());

    return 1;
}
