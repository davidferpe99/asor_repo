#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){
   struct utsname info;

   if (uname(&info) == -1){
       printf("ERROR(%d): %s\n", errno, strerror(errno));
       return -1;
   }
   else{
       printf ("Nombre del Sistema:  %s\n", info.sysname);
       printf ("Nombre del nodo: %s\n", info.nodename);
       printf ("Release: %s\n", info.release);
       printf ("Versión: %s\n", info.version);
       printf ("Máquina: %s\n", info.machine);

   }

    return 1;
}
