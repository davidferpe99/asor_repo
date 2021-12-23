#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX 80

volatile int stop = 0;

void hler(int signal){
    pid_t pid;
    pid = wait(NULL);

    printf("PID exit");
}

int main(int argc, char ** argv){

    struct addrinfo *res;
    struct addrinfo hints;
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    int sock, socktop;
    char buff[MAX];
    int nr_bytes;
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    int out = 0;
    pid_t pid;
    ssize_t c;

    if (argc != 3){
        fprintf(stderr, "Uso: ./Ejercicio9 <address> <port>\n");
        return -1;
    }

    
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(argv[1], argv[2], &hints, &res) < 0){
        fprintf(stderr, "Error en getaddrinfo(): Nombre o servicio desconocido\n");
        return -1;
    }

    sock = socket(res->ai_family, res->ai_socktype, 0);

    bind(sock, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res);

    listen(sock, 5);

    signal(SIGCHLD, hler);

    int status;

    while(1){
        socktop = accept(sock, (struct sockaddr *) &addr, &addrlen);
        
        pid = fork();

        if (pid == 0){
            while(1){
                getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
                printf("[%i] Conexión desde el host: %s Port: %s\n", getpid(), host, serv);

                nr_bytes = recv(socktop, buff, MAX, 0);
                buff[nr_bytes] = '\0';

                if ((buff[0] == 'q') && (nr_bytes == 2)){
                    printf("COnexión terminada...\n");
                    return -1;
                }
                else{
                    send(addrlen, buff, nr_bytes, 0);
                }

            }
        }
        else{
            pid = wait(&status);
            close(socktop);
            return -1;
        }
    }
    close(socktop);

    return 0;

    
}
