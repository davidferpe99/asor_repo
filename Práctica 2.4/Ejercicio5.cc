#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

#define MAX 256

int main(){
    int fifo1, fifo2, nfds, mods, num_bytes;
    char buffer[MAX];
    fd_set set;
    struct timeval timeout;

    while (1){
        if ((fifo1 = open("fifo1", O_RDONLY | O_NONBLOCK)) < 0){
            perror("open");
            return -1;
        }

        if ((fifo2 = open("fifo2", O_RDONLY | O_NONBLOCK)) < 0){
            perror("open");
            return -1;
        }

        FD_ZERO(&set);
        FD_SET(fifo1, &set);
        FD_SET(fifo2, &set);

        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

        if (fifo1 > fifo2){
            nfds = fifo1 +1;
        }
        else{
            nfds = fifo2 +1;
        }

        mods = select(nfds, &set, NULL, NULL, &timeout);

        if (mods == -1){
            perror("select");
        }
        else if(mods){
            num_bytes = read(fifo1, buffer, MAX-1);
            buffer[num_bytes] = '\0';
            if (num_bytes != 0){
                printf("Nuevo dato de fifo1: %s\n", buffer);
            }
            num_bytes = read(fifo2, buffer, MAX-1);
            buffer[num_bytes] = '\0';

            if (num_bytes != 0){
                printf("Nuevo dato de fifo2: %s\n", buffer);
            }
        }
        else{
            printf("Sin datos nuevos durante 2 segundos\n");
        }

        close(fifo1);
        close(fifo2);
    }

    return 0;
}
