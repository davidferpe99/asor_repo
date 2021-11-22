#include <stdio.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main(){
    int policy, priority, min, max;

    if ((policy = sched_getscheduler(0)) < 0){
        perror("sched_getscheduler");
        return -1;
    }

    errno = 00;
    priority = getpriority(PRIO_PROCESS, 0);
    if (errno != 0){
        perror("getpriority");
        return -1;
    }

    if ((min == sched_get_priority_min(policy)) < 0){
        perror("sched_get_priority_min");
        return -1;
    }

    if ((max == sched_get_priority_max(policy)) < 0){
        perror("sched_get_priority_max");
        return -1;
    }

    switch (policy){
        case 0: printf("Prioridad de planificación: SCHED_OTHER.\n"); break;
        case 1: printf("Prioridad de planificación: SCHED_FIFO.\n"); break;
        case 2: printf("Prioridad de planificación: SCHED_RR.\n"); break;
        case 3: printf("Prioridad de planificación:: SCHED_BATCH.\n"); break;
        case 5: printf("Prioridad de planificación:SCHED_IDLE.\n"); break;
        case 4: printf("Prioridad de planificación: SCHED_DEADLINE.\n"); break;
        default: printf("SchedulingPrioridad de planificación: policy: UNKNOWN.\n"); break;
    }

    printf("Prioridad de planificación: %d.\n", priority);
    printf("MIN: %d MAX: %d\n", min, max);

    return 0;
}
