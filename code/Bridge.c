#include "util.h"

typedef struct {
    int sz;
    pthread_mutex_t *bridge;
} Bridge;


Bridge* init(int n){
    Bridge *b = (Bridge*)malloc(sizeof(Bridge));
    b->sz = n;
    b->bridge = (pthread_mutex_t*)calloc(n, sizeof(pthread_mutex_t));
    return b;
}
