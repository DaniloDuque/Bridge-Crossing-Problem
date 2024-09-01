#ifndef BRIDGE_H
#define BRIDGE_H

#include "util.h"

typedef struct{
    int frst; mutex scnd;
} mtx;

typedef struct {
    int sem, sz, dir, amb_waiting, t1, t2;
    mtx *bridge;
} Bridge;

Bridge* init(int n){
    Bridge *b = (Bridge*)malloc(sizeof(Bridge));
    b->sz = n; b->dir = 0;
    b->bridge = (mtx*)malloc((n+2)*sizeof(mtx));
    for(int i = 0; i<n+2; ++i) b->bridge[i].frst = 0, pthread_mutex_init(&b->bridge[i].scnd, NULL);
    b->t1 = 0;
    b->t2 = 0;
    b->amb_waiting=0;
    b->sem = 1;
    return b;
}

#endif 
