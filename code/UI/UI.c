#include "../Bridge.h"
#include "../util.h"

void *UICarnage(void *arg){
    Bridge *b = (Bridge*)arg;
    while(1){
        zzz(micro/15);
        printf("\033[H\033[J");
        printf("+");
        for (int i = 0; i <= b->sz + 6; ++i) printf("--");
        printf("-+\n");
        printf("| %c ", (b->value[0]==1)? 'C' : (b->value[0])? 'A' : ' ');
        printf((b->amb_waiting && b->dir==1)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" | ");
        for (int i = 1; i<=b->sz; ++i) printf((b->value[i]==2)? "A " : (b->value[i])? "C " : "_ ");
        printf("| " );
        printf((b->amb_waiting && b->dir==-1)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" %c |\n+", (b->value[b->sz+1]==1)? 'C' : (b->value[b->sz+1])? 'A' : ' ');
        for (int i = 0; i<=b->sz + 6; ++i) printf("--");
        printf("-+\n");
    }
}

void *UISemaphore(void *arg){
    Bridge *b = (Bridge*)arg;
    while(1){
        zzz(micro/15);
        printf("\033[H\033[J");
        printf("+");
        for (int i = 0; i <= b->sz + 6; ++i) printf("--");
        printf("-+\n");
        printf("| %c ", (b->value[0]==1)? 'C' : (b->value[0])? 'A' : ' ');
        printf((b->sem != 1)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" | ");
        for (int i = 1; i<=b->sz; ++i) printf((b->value[i]==2)? "A " : (b->value[i])? "C " : "_ ");
        printf("| " );
        printf((b->sem != -1)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" %c |\n+", (b->value[b->sz+1]==1)? 'C' : (b->value[b->sz+1])? 'A' : ' ');
        for (int i = 0; i<=b->sz + 6; ++i) printf("--");
        printf("-+\n");
    }
}

void *UITraffic(void * arg){
    Bridge *b = (Bridge *)arg;
    while (1) {
        zzz(micro/15);
        printf("\033[H\033[J");
        printf("+");
        for (int i = 0; i <= b->sz + 10; ++i) printf("--");
        printf("-+\n");
        printf("| %d ", b->t1);
        printf("| %c ", (b->value[0]==1)? 'C' : (b->value[0])? 'A' : ' ');
        printf((b->sem != 1 && !b->amb_waiting)? "  " : (b->amb_waiting)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" | ");
        for (int i = 1; i<=b->sz; ++i) printf((b->value[i]==2)? "A " : (b->value[i])? "C " : "_ ");
        printf("| " );
        printf((b->sem != -1 && !b->amb_waiting)? "  " : (b->amb_waiting)? RED_CIRCLE : GREEN_CIRCLE);
        printf(" %c |", (b->value[b->sz+1]==1)? 'C' : (b->value[b->sz+1])? 'A' : ' ');
        printf(" %d |\n+", b->t2);
        for (int i = 0; i<=b->sz + 10; ++i) printf("--");
        printf("-+\n");
    }
}
