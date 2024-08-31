#include "Bridge.h"
#include "util.h"

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
        for (int i = 0; i <= b->sz + 6; ++i) printf("--");
        printf("-+\n");
        printf("| %c ", (b->bridge[0].frst==1)? 'C' : (b->bridge[0].frst)? 'A' : ' ');
        printf((b->sem != 1)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" | ");
        for (int i = 1; i<=b->sz; ++i) printf((b->bridge[i].frst==2)? "A " : (b->bridge[i].frst)? "C " : "_ ");
        printf("| " );
        printf((b->sem != -1)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" %c |\n+", (b->bridge[b->sz+1].frst==1)? 'C' : (b->bridge[b->sz+1].frst)? 'A' : ' ');
        for (int i = 0; i<=b->sz + 6; ++i) printf("--");
        printf("-+\n");
    }
}

void *UITraffic(void * arg){
    Bridge *b = (Bridge *)arg;
    while (1) {
        usleep(micro/10);
        system("clear");
        printf("+");
        for (int i = 0; i <= b->sz + 10; ++i) printf("--");
        printf("-+\n");
        printf("| %d ", b->t1);
        printf("| %c ", (b->bridge[0].frst==1)? 'C' : (b->bridge[0].frst)? 'A' : ' ');
        printf((b->sem != 1 && !b->amb_waiting)? "  " : (b->amb_waiting)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" | ");
        for (int i = 1; i<=b->sz; ++i) printf((b->bridge[i].frst==2)? "A " : (b->bridge[i].frst)? "C " : "_ ");
        printf("| " );
        printf((b->sem != -1 && !b->amb_waiting)? "  " : (b->amb_waiting)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" %c |", (b->bridge[b->sz+1].frst==1)? 'C' : (b->bridge[b->sz+1].frst)? 'A' : ' ');
        printf(" %d |\n+", b->t2);
        for (int i = 0; i<=b->sz + 10; ++i) printf("--");
        printf("-+\n");
    }
}
