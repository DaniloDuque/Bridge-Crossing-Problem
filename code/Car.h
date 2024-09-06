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

void* EnterAmbulance(void *arg) {
    Car* car = (Car*)arg;
    int st = start(car), end = end(car);
    lock(&cz->bridge[st-car->dir].scnd); lock(&bridge_mutex);  
    cz->bridge[st-car->dir].frst = 2; cz->amb_waiting++;
    while((car->dir == 1)? cz->dir<0 : cz->dir>0) wait(&empty, &bridge_mutex);
    cz->dir += car->dir; --cz->amb_waiting; unlock(&bridge_mutex);  
    CrossBridge(car, st, end, 2); 
    lock(&bridge_mutex);  
    cz->dir -= car->dir; cz->bridge[end].frst = 0;
    if (cz->dir == 0) signal(&empty);  
    unlock(&bridge_mutex); unlock(&cz->bridge[end].scnd);  
    free(car);  
    return 0;
}

#endif // !CAR_H
