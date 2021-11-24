#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){
    char *comm[3];
    pid_t pid, hijo_pid, sid;
    char *dir = "/tmp";
    int status, fd0, fd1, fd2;

    if (argc != 2){
        fprintf(stderr, "Número incorrcto de argumentos.\n Uso: ./daemon \"<program>\"\n");
        return -1;
    }

    hijo_pid = fork();

    switch(hijo_pid){
        case -1:
            perror("fork");
            exit(1);
        case 0:
            pid = getpid();
            sid = setsid();

            if (chdir(dir) < 0){
                perror("chdir");
                return -1;
            }
            printf("Proceso hijo: %i (padre: %i)\n", pid, getppid());
            printf("Sid: %d\n", sid);
            printf("Directorio actual de trabajo: %s\n", dir);

            comm[0] = strtok(argv[1], "");
            comm[1] = strtok(NULL, "");
            comm[2] = NULL;

            if ((fd0 = open("/tmp/daemon.out", O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0) {
                perror("open");
                return -1;
            }

            if ((fd1 = open("/tmp/daemon.out", O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0) {
                perror("open");
                return -1;
            }

            if ((fd2 = open("/tmp/daemon.out", O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0) {
                perror("open");
                return -1;
            }

            if (dup2(fd0, 0) < 0){
                perror("dup2");
                return -1;
            }

            if (dup2(fd1, 0) < 0){
                perror("dup2");
                return -1;
            }

            if (dup2(fd2, 0) < 0){
                perror("dup2");
                return -1;
            }

            execvp(comm[0], comm);

            if (close(fd0) < 0){
                perror("close");
                return -1;
            }

            if (close(fd1) < 0){
                perror("close");
                return -1;
            }

            if (close(fd2) < 0){
                perror("close");
                return -1;
            }

        break;

        default: 
            pid = getpid();

            wait(&status);

            printf("Proceso padre: %i (hijo: %i)\n", pid, hijo_pid);

        break;
    }

    return 0;
}
