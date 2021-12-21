#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX 80

int main(int argc, char **argv){
    struct addrinfo *res;
    struct addrinfo hints;
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    int sock, std_in = 0, out = 0, mods;;
    fd_set set;
    char buff[MAX];
    int nr_bytes;
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    time_t secs;

    if (argc != 3){
        fprintf(stderr, "Usage: ./udpserv <address> <port>\n");
        return -1;
    }

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if (getaddrinfo(argv[1], argv[2], &hints, &res) < 0){
        fprintf(stderr, "Error en getaddrinfo(): Nombre o servicio desconocido\n");
        return -1;
    }

    sock = socket(res->ai_family, res->ai_socktype, 0);

    bind(sock, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

    while(!out){
        FD_ZERO(&set);

        FD_SET(std_in, &set);

        FD_SET(sock, &set);

        mods = select(sock+1, &set, NULL, NULL, NULL);

        if (mods == -1){
            perror("select");
        }
        else{
            if (FD_ISSET(std_in, &set)){
                nr_bytes = read(std_in, buff, MAX);
                buff[nr_bytes] = '\0';

                if (strncmp(buff, "t", strlen(buff)-1) == 0){
                    time(&secs);
                    nr_bytes = strftime(buff, MAX, "%I:%M:%S %p", localtime(&secs));
                    printf("%s\n", buff);
                }
                else if(strncmp(buff, "d", strlen(buff)-1) == 0){
                    out = 1;
                    printf("Saliendo...\n");
                }
                else{
                    printf("Comando no soportado %s", buff);
                }
            }
            else if (FD_ISSET(sock, &set)){
                nr_bytes = recvfrom(sock, buff, MAX, 0, (struct sockaddr *) &addr, &addrlen);
                buff[nr_bytes] = '\0';

                getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

                printf("%d bytes de %s:%s\n", nr_bytes, host, serv);

                if (strncmp(buff, "t", strlen(buff)-1) == 0){
                    time(&secs);
                    nr_bytes = strftime(buff, MAX, "%I:%M:%S %p", localtime(&secs));

                    sendto(sock, buff, nr_bytes, 0, (struct sockaddr *) &addr, addrlen);
                }
                else if(strncmp(buff, "d", strlen(buff)-1) == 0) {
                    time(&secs);
                    nr_bytes = strftime(buff, MAX, "%G-%m-%d", localtime(&secs));

                    sendto(sock, buff, nr_bytes, 0, (struct sockaddr*) &addr, addrlen);
                }
                else if(strncmp(buff, "q", strlen(buff)-1) == 0){
                    out = 1;
                    printf("Saliendo...\n");
                    sendto(sock, " ", 1, 0, (struct sockaddr *) &addr, addrlen);
                }
            }
        }
    }
    close(sock);
    return 0;


}
