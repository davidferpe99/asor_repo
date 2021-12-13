#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv){
    struct addrinfo *res;
    char host[NI_MAXHOST];

    if (argc != 2){
        fprintf(stderr, "Uso: ./Ejercicio1 <hostname>\n");
        return 1;
    }

    if (getaddrinfo(argv[1], NULL, NULL, &res) < 0){
        fprintf(stderr, "Error en getaddrinfo(): Nombre o servicio desconocido\n");
        return -1;
    }

    while (res != NULL){
        getnameinfo(res->ai_addr, res->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
        printf("%s\t%d\t%d\n", host, res->ai_family, res->ai_socktype);
        res = res->ai_next;
    }

    return 0;
}
