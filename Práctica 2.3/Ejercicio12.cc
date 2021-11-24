#include <stdio.h>
#include <signal.h>

int sigint = 0;
int sigtstp = 0;

void handler(int signal){
    if (signal == SIGINT){
        sigint++;
    }
    else if (signal == SIGTSTP){
        sigtstp++;
    }
}

int main(){
    struct sigaction act;
    sigset_t set;

    sigaction(SIGINT, NULL, &act);
    acts.sa_handler = handler;

    if (sigaction(SIGINT, &act, NULL) < 0){
        perror("sigaction");
        return -1;
    }

    if (sigaction(SIGTSTP, &act, NULL) < 0){
        perror("sigaction");
        return -1;
    }

    while (sigint + sigtstp < 10){
        sigsuspend(&set);
    }

    printf("\nSIGINT: %d veces\n", sigint);
    printf("\nSIGTSTP: %d veces\n", sigtstp);

    return 0;
}
