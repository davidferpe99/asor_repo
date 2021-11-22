#include <stdio.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <unistd.h>

#define SIZE 100

int main(){
    pid_t pid, ppid, pgid, sid;
    char cwd[SIZE];
    struct rlimit rlim;

    pid = getpid();
    ppid = getppid();

    if ((pgid = getpgid(pid)) < 0){
        perror("getgpid");
        return -1;
    }

    if ((sid = getsid(pid)) < 0){
        perror("getsid");
        return -1;
    }

    if (getrlimit(RLIMIT_OFILE, &rlim) < 0){
        perror("getrlimit");
        return -1;
    }

    if (getcwd(cwd,SIZE) == NULL){
        perror("getcwd");
        return -1;
    }

    printf("Pid: %d.\n", pid);
    printf("Ppid: %d.\n", ppid);
    printf("Pgid: %d.\n", pgid);
    printf("Sid: %d.\n", sid);
    printf("Número máximo de ficheros abiertos: %lu.\n", rlim.rlim_max);
    printf("Directorio de trabajo actual: %s.\n", cwd);

    return 0;
}
