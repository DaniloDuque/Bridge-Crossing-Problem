#ifndef BRIDGE_H
#define BRIDGE_H

#include "util.h"

typedef struct{
    int frst; pthread_mutex_t scnd;
} mtx;

typedef struct {
    int sz, dir;
    pthread_mutex_t access;
    mtx *bridge;
} Bridge;

Bridge* init(int n){
    Bridge *b = (Bridge*)malloc(sizeof(Bridge));
    b->sz = n;
    b->dir = 0;
    b->bridge = (mtx*)malloc((n+2)*sizeof(mtx));
    for(int i = 0; i<n+2; ++i) b->bridge[i].frst = 0, pthread_mutex_init(&b->bridge[i].scnd, NULL);
    pthread_mutex_init(&b->access, 0);
    return b;
}

#endif 
