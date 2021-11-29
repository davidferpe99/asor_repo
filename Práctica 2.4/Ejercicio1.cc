#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv){
    pid_t hijo;
    char *comando[3];
    int tuberia_fd[2];


    if (argc != 5){
        fprintf(stderr, "Número de argumentoss incorrecto.\n Uso: ./tuberia <comando1> <argumento1> <comando2> <argumento2>\n");
        return 1;
    }

    pipe(tuberia_fd);

    hijo = fork();

    switch(hijo){
        case 0:
            dup2(tuberia_fd[0], 0);

            close(tuberia_fd[0]);
            close(tuberia_fd[1]);

            comando[0] = argv[3];
            comando[1] = argv[4];
            comando[2] = NULL;
            execvp(comando[0], comando);
        break;

        default:
            dup2(tuberia_fd[1], 1);

            close(tuberia_fd[0]);
            close(tuberia_fd[1]);

            comando[0] = argv[1];
            comando[1] = argv[2];
            comando[2] = NULL;
            execvp(comando[0], comando);

        break;
    }

    return 0;
}
