#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX 80

int main(int argc, char **argv){
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

    if (argc != 3){
        fprintf(stderr, "Uso: ./Ejercicio8 <address> <port>\n");
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

    listen(sock, 5);

    while (1){
        socktop = accept(sock, (struct sockaddr *) &addr, &addrlen);
        pid = fork();

        if (pid == 0){
            getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
            printf("[%i] Conexión desde el host: %s Port: %s\n", getpid(), host, serv);
            
            while(!out){
                while((nr_bytes = recv(socktop, buff, MAX, 0))){
                    buff[nr_bytes] = '\0';
                    printf("\t Mensaje: %s", buff);

                    if (strncmp(buff, "Q", strlen(buff)-1) == 0){
                        out = 1;
                        printf("[%i] Conexión terminada...\n", getpid());
                        strcpy(buff, " ");
                    }

                    send(socktop, buff, nr_bytes, 0);
                  
                }
            }
            close(socktop);
            return 0;
        }

        
    }
  
    close(sock);

    return 0;
}
