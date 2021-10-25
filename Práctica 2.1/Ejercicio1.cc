#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main (){
    char *c;
    if (setuid(0) == -1){
        perror(c);
    }
    
    return 1;
}
