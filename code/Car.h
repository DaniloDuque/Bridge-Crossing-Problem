#ifndef CAR_H
#define CAR_H

#include "util.h"
#include "Bridge.h"

extern Bridge* cz; 
pthread_mutex_t bridge_mutex;
pthread_cond_t empty;

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
    c->v = rrand(l, u);
    c->dir = d;
    return c;
}

void CrossBridge(Car * c, int st, int end, int amb){
    for(int i = st; i!=end+c->dir; i+=c->dir){
        lock(&cz->bridge[i].scnd);
        cz->bridge[i-c->dir].frst=0;
        unlock(&cz->bridge[i-c->dir].scnd);
        cz->bridge[i].frst=amb;
        usleep(micro/c->v);
    }
}

void *CrossAmbulance(void *arg){
    Car* amb = (Car*)arg;
    int start = (amb->dir==1)? 1 : cz->sz, end = (start==1)? cz->sz : 1;
    lock(&cz->bridge[start-amb->dir].scnd); lock(&bridge_mutex); ++cz->amb_waiting;
    while((amb->dir == 1) ? cz->dir < 0 : cz->dir > 0) pthread_cond_wait(&empty, &bridge_mutex);
    cz->dir+=amb->dir; --cz->amb_waiting;
    unlock(&bridge_mutex);
    CrossBridge(amb, start, end, 2);
    lock(&bridge_mutex);
    cz->dir-=amb->dir; cz->bridge[end].frst=0;
    if(cz->dir == 0) pthread_cond_broadcast(&empty);
    unlock(&bridge_mutex); unlock(&cz->bridge[end].scnd);
    return 0;
}

#endif // !CAR_H
