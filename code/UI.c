#include "Bridge.h"

void *print(void * arg){
    Bridge *b = (Bridge*)arg;
    while(1){
        usleep(micro/10);
        system("clear");
        for(int i = 1; i<=b->sz; ++i) (b->bridge[i].frst)? printf("%c ", (b->bridge[i].frst == 2)? 'A' : 'C') : printf("_ ");
        puts("");
    }
}
