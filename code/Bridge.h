#ifndef BRIDGE_H
#define BRIDGE_H

#include "util.h"

typedef struct {
    int sem, sz, dir, amb_waiting, t1, t2;
    mutex *mtx;
    int *value;
} Bridge;

Bridge* init(int n){
    Bridge *b = (Bridge*)malloc(sizeof(Bridge));
    b->sz = n; b->dir = 0;
    b->mtx = (mutex*)malloc((n+2)*sizeof(mutex));
    b->value = (int*)calloc(n+2, sizeof(int));
    for(int i = 0; i<n+2; ++i) pthread_mutex_init(&b->mtx[i], NULL);
    b->t1 = 0; b->t2 = 0; b->amb_waiting=0; b->sem = -1;
    return b;
}

#endif 
