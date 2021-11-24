#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    sigset_t blk_set, pending;

    if (sigemptyset(&blk_set) < 0){
        perror("sigemptyset");
        return -1;
    }

    if (sigaddset(&blk_set, SIGINT) < 0){
        perror("sigaddset");
        return -1;
    }

    if (sigaddset(&blk_set, SIGTSTP) < 0){
        perror("sigaddset");
        return -1;
    }

    if (sigprocmask(SIG_BLOCK, &blk_set, NULL) < 0){
        perror("sigprocmask");
        return -1;
    }

    setenv("SLEEP_SECS", "6", 1);
    sleep(atoi(getenv("SLEEP_SECS")));

    if (sigpending(&pending) < 0){
        perror("sigpending");
        return -1;
    }

    if (sigismember(&pending, SIGINT) == 1){
        printf("SIGINT recibido\n");
    }

    if (sigismember(&pending, SIGTSTP) == 1){
        printf("SIGTSTP recibido\n");
    }

    sigdelset(&blk_set, SIGINT);

    if (sigprocmask(SIG_UNBLOCK, &blk_set, NULL) < 0){
        perror("sigprocmask");
        return -1;
    }

    printf("Finalizado\n");

    return 0;

}
