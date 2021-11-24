#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    sigset_t set, pending;
    int secs, delet = 1;

    if (argc != 2){
        printf("Número incorreecto de argumentos.\n Uso: ./deleter \"<segundos>\"\n");
        return -1;
    }

    if (sigfillset(&set) < 0){
        perror("sigfillset");
        return -1;
    }

    if (sigprocmask(SIG_BLOCK, &set, NULL) < 0){
        perror("sigprocmask");
        return -1;
    }

    secs = atoi(argv[1]);

    sleep(secs);

    if (sigpending(&pending) < 0){
        perror("sigpending");
        return -1;
    }

    if (sigismember(&pending, SIGUSR1) == 1){
        printf("SIGUSR1 recibido\n");
        delet = 0;
    }

    if (sigemptyset(&set) < 0){
        perror("sigemptyset");
        return -1;
    }

    if (sigprocmask(SIG_UNBLOCK, &set, NULL) < 0){
        perror("sigprocmask");
        return -1;
    }

    if (delet == 1){
        printf("Borrando fichero\n");
        unlink(argv[0]);
    }
    else{
        printf("Cancelando el borrado de fichero\n");
    }

    return 0;
}
