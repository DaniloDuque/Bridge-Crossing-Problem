#include "Bridge.h"
#include <unistd.h>

void *UICarnage(void *arg) {
    Bridge *b = (Bridge *)arg;
    while (1) {
        usleep(micro / 10);
        system("clear");
        printf("+");
        for (int i = 0; i <= b->sz + 3; ++i) printf("--");
        printf("+\n");
        printf("| ");
        printf((b->amb_waiting) ? RED "A" COLOR_RESET : GREEN "C" COLOR_RESET);
        printf(" | ");
        for (int i = 1; i <= b->sz; ++i) printf((b->bridge[i].frst==2)? "A " : (b->bridge[i].frst)? "C " : "_ ");
        printf("| " );
        printf((b->amb_waiting) ? RED "A" COLOR_RESET : GREEN "C" COLOR_RESET);
        printf("|\n+");
        for (int i = 0; i <= b->sz + 3; ++i) printf("--");
        printf("+\n");
    }
}

void *UISemaphore(void *arg){
    Bridge *b = (Bridge*)arg;
    while(1){
        usleep(micro/10);
        system("clear");
        printf("+");
        for (int i = 0; i <= b->sz + 3; ++i) printf("--");
        printf("+\n");
        printf("| ");
        printf((b->sem != 1) ? RED " " COLOR_RESET : GREEN " " COLOR_RESET);
        printf(" | ");
        for (int i = 1; i <= b->sz; ++i) printf((b->bridge[i].frst==2)? "A " : (b->bridge[i].frst)? "C " : "_ ");
        printf("| " );
        printf((b->sem != -1) ? RED " " COLOR_RESET : GREEN " " COLOR_RESET);
        printf("|\n+");
        for (int i = 0; i <= b->sz + 3; ++i) printf("--");
        printf("+\n");
    }
}

void *UITraffic(void * arg){
    while(1){

    }
}
