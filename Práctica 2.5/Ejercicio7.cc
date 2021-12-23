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
    int sock;
    char buff[MAX];
    int nr_bytes;
    

    if (argc != 3){
        fprintf(stderr, "Uso: ./Ejercicio7 <address> <port>\n");
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

    if (connect(sock, (struct sockaddr *) res->ai_addr, res->ai_addrlen) < 0){
        fprintf(stderr, "Error al conectar con el socket\n");
        return -1;
    }

    strcpy(buff, " \n");

    while(strncmp(buff, "Q", strlen(buff)-1) != 0){
        nr_bytes = read(0, buff, MAX);
        buff[nr_bytes] = '\0';
        send(sock, buff, nr_bytes, 0);
        nr_bytes = recv(sock, buff, MAX, 0);
        buff[nr_bytes] = '\0';
        printf("%s", buff);
    }

    close(sock);

    return 0;
}
