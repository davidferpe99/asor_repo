#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX 20

int main(){
    pid_t hijo;
    int p_h[2], h_p[2];
    char buf[MAX];
    int num_bytes, cnt = 0;
    char confirm = 'l';

    pipe(p_h);
    pipe(h_p);

    hijo = fork();

    switch(hijo){
        case 0:
            close(p_h[1]);
            close(h_p[0]);

            while(cnt < 10){
                num_bytes = read(p_h[0], buf, MAX);
                write(1, buf, num_bytes);
                sleep(1);

                if (cnt == 9){
                    confirm = 'q';
                }
                write(h_p[1], &confirm, 1);
                cnt++;
            }

            close(p_h[0]);
            close(h_p[1]);
        break;

        default:
            close(p_h[0]);
            close(h_p[1]);

            while(confirm != 'q'){
                num_bytes = read(0, buf, MAX);
                write(p_h[1], buf, num_bytes);
                read(h_p[0], &confirm, 1);
            }

            close(p_h[1]);
            close(h_p[0]);

        break;
    }
    return 0;
}
