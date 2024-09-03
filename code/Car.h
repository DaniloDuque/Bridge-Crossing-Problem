#ifndef CAR_H
#define CAR_H

#include "util.h"
#include "Bridge.h"

extern Bridge* cz; 
extern mutex bridge_mutex;
extern cond empty;

typedef struct{
    int dir;
    double v;
} Car;

typedef struct{
    int dir;
    double mu, lbv, ubv, ambProb;
} domain;

Car * CreateCar(double l, double u, double p, int d){
    Car * c = (Car*)malloc(sizeof(Car));
    c->v = rrand(l, u); c->dir = d;
    return c;
}

void CrossBridge(Car * c, int st, int end, int amb){
    for(int i = st; i!=end+c->dir; i+=c->dir){
        lock(&cz->bridge[i].scnd);
        cz->bridge[i-c->dir].frst=0;
        unlock(&cz->bridge[i-c->dir].scnd);
        cz->bridge[i].frst=amb;
        zzz(micro/c->v);
    }
}

void *CrossAmbulance(void *arg){
    Car* amb = (Car*)arg;
    int st = start(amb), end = end(amb);
    lock(&cz->bridge[st-amb->dir].scnd); lock(&bridge_mutex); 
    ++cz->amb_waiting; cz->bridge[st-amb->dir].frst=2;
    while((amb->dir==1)? cz->dir<0 : cz->dir>0) wait(&empty, &bridge_mutex);
    cz->dir+=amb->dir; --cz->amb_waiting;
    unlock(&bridge_mutex);
    CrossBridge(amb, st, end, 2);
    cz->dir-=amb->dir; cz->bridge[end].frst=0;
    if(cz->dir==0) signal(&empty);
    unlock(&cz->bridge[end].scnd);
    free(amb);
    return 0;
}

#endif // !CAR_H
