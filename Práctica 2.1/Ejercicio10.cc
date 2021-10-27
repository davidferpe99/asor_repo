#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <pwd.h>

int main(){

    printf("UID real: %d\n", getuid());
    printf("UID efectivo: %d\n", geteuid());
    
    uid_t uid = getuid();
    struct passwd *pass= getpwuid(uid);

    char *UserName = pass->pw_name;
    char *home = pass->pw_dir;
    char *info = pass->pw_gecos;
   

    printf("Username: %s\n", UserName);
    printf("Home: %s\n", home);
    printf("Descripción: %s\n",info);

    return 1;
}
