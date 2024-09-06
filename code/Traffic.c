#include "Car.h"
#include "Bridge.h"
#include "util.h"

extern Bridge* cz;
extern cond empty;  
cond pass = INIT_COND;
extern mutex bridge_mutex;  
mutex clear = INIT_MUTEX;
extern int k_i, k_j;

void reset(int i) {
    cz->sem *= -1;
    if(i) cz->t1 = k_i;
    else cz->t2 = k_j;
}

void *run_Traffic() {
    while (1) {
        reset(1);
        lock(&bridge_mutex);
        if(cz->dir) wait(&empty, &bridge_mutex);
        broadcast(&pass);  
        while (cz->t1>0){
            if(!cz->dir && !cz->amb_waiting && !cz->bridge[0].frst && cz->bridge[cz->sz+1].frst) break;
            wait(&empty, &bridge_mutex);  
        }unlock(&bridge_mutex);
        reset(0);
        lock(&bridge_mutex);
        if(cz->dir) wait(&empty, &bridge_mutex);
        broadcast(&pass);
        while(cz->t2>0){
            if(!cz->dir && !cz->amb_waiting && cz->bridge[0].frst && !cz->bridge[cz->sz+1].frst) break;
            wait(&empty, &bridge_mutex);  
        }unlock(&bridge_mutex);
    }
}

void* EnterTrafficCar(void *arg) {
    Car* car = (Car*)arg;
    int st = start(car), end = end(car);
    lock(&cz->bridge[st - car->dir].scnd);  
    cz->bridge[st - car->dir].frst = 1;
    if(!cz->dir) broadcast(&empty);
    lock(&bridge_mutex);
    while(cz->amb_waiting || ((car->dir == 1)? cz->t1<=0 : cz->t2<=0) || (cz->sem!=car->dir)) wait(&pass, &bridge_mutex);              
    cz->dir += car->dir; (car->dir==1)? --cz->t1 : --cz->t2; 
    unlock(&bridge_mutex);  
    CrossBridge(car, st, end, 1);  
    lock(&bridge_mutex);  
    cz->dir -= car->dir; cz->bridge[end].frst = 0;
    if(!cz->dir) broadcast(&empty);
    unlock(&bridge_mutex); unlock(&cz->bridge[end].scnd);  
    free(car);  
    return 0;
}




//Still deadlock
void* EnterTrafficAmbulance(void *arg) {
    Car* car = (Car*)arg;
    int st = start(car), end = end(car);
    lock(&cz->bridge[st-car->dir].scnd); lock(&bridge_mutex);  
    cz->bridge[st-car->dir].frst = 2; cz->amb_waiting++;
    while((car->dir==1)? cz->dir<0 : cz->dir>0) wait(&empty, &bridge_mutex);
    if(car->dir==cz->sem) (car->dir==1)? --cz->t1 : --cz->t2;
    cz->dir += car->dir; --cz->amb_waiting; unlock(&bridge_mutex);  
    CrossBridge(car, st, end, 2); 
    lock(&bridge_mutex);  
    cz->dir -= car->dir; cz->bridge[end].frst = 0;
    if (cz->dir == 0) broadcast(&empty);  
    unlock(&bridge_mutex); unlock(&cz->bridge[end].scnd);  
    free(car);  
    return 0;
}

void* TrafficCarGenerator(double mu, double l, double u, double p, int d){
    while(1){
        zzz(-mu*log(1-prob())*micro);
        thread t;
        create(&t, (prob()<p)? EnterTrafficAmbulance : EnterTrafficCar, CreateCar(l, u, p, d));
        detach(t);
    }
}

void* run_generator_Traffic(void* arg) {
    domain* dom = (domain*)arg;
    TrafficCarGenerator(dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}
