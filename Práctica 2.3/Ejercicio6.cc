#include <stdio.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>

int main(){
    pid_t pid, ppid, pgid, sid, child_pid;
    char *dir = "/tmp";
    struct rlimit rlim;
    int status;

    child_pid = fork();
    switch (child_pid){
        case -1: 
            perror("fork");
            exit(1);
        case 0:
            pid = getpid();
            sid = setsid();

            if ((pgid = getpgid(pid)) < 0){
                perror("getgpid");
                return -1;
            }

             if (getrlimit(RLIMIT_OFILE, &rlim) < 0){
                perror("getrlimit");
                return -1;
            }

            if (chdir(dir) < 0){
                perror("chdir");
                return -1;
            }

            printf("Proceso hijo %i (padre: %i).\n", pid, getppid());
            printf("Pgid: %d.\n", pgid);
            printf("Sid: %d.\n", sid);
            printf("Número máximo de ficheros abiertos: %lu.\n", rlim.rlim_max);
            printf("Directorio de trabajo actual: %s.\n", dir);
            exit(0);
        break;

        default: 
            pid = getpid();

            wait(&status);

            printf("Proceso padre %i (hijo: %i)\n", pid, child_pid);
    }

    return 0;
}
