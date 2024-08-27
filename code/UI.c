#include "Bridge.h"

void *print(void * arg){
    Bridge *b = (Bridge*)arg;
    while(1){
        sleep(1);
        fflush(stdout);
        for(int i = 1; i<=b->sz; ++i) printf("%d ", b->bridge[i].frst);
        puts("");
    }
}
