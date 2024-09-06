#include "Car.h"
#include "Bridge.h"
#include "util.h"

extern Bridge* cz;
extern cond empty;
cond pass = INIT_COND;
extern mutex bridge_mutex;
mutex clear = INIT_MUTEX; 
extern int k_i, k_j;

void reset(){
    cz->sem*=-1;cz->t1=k_i;cz->t2=k_j;
}

int id=0;
void *run_Traffic() {
    while (1) {
        reset();
        broadcast(&pass);
        while(cz->amb_waiting || (cz->t1>0)){
            if(!cz->dir && !cz->amb_waiting && !cz->bridge[0].frst && cz->bridge[cz->sz+1].frst) break;
            DEBUG(id++);
            wait(&empty, &bridge_mutex);
        }reset();
        broadcast(&pass);
        while(cz->amb_waiting || (cz->t2>0)) {
            if(!cz->dir && !cz->amb_waiting && cz->bridge[0].frst && !cz->bridge[cz->sz+1].frst) break;
            DEBUG(id++);
            wait(&empty, &bridge_mutex);
        }
    }
}

void* CrossTrafficCar(void *arg) {
    Car* car = (Car*)arg;
    int st = start(car), end = end(car);
    lock(&cz->bridge[st-car->dir].scnd); 
    cz->bridge[st-car->dir].frst=1; 
    if(!cz->dir) broadcast(&empty);
    while(cz->amb_waiting || ((car->dir==1)? cz->t1<=0 : cz->t2<=0) || (car->dir!=cz->sem)) wait(&pass, &bridge_mutex), DEBUG(id++);
    (car->dir==1)? --cz->t1 : --cz->t2;
    cz->dir += car->dir;
    CrossBridge(car, st, end, 1);
    cz->dir -= car->dir;
    cz->bridge[end].frst = 0;
    if (!cz->dir) broadcast(&empty);
    unlock(&cz->bridge[end].scnd);
    free(car);
    return 0;
}

void *CrossTrafficAmbulance(void *arg){
    Car* amb = (Car*)arg;
    int st = start(amb), end = end(amb);
    lock(&cz->bridge[st-amb->dir].scnd); 
    ++cz->amb_waiting; cz->bridge[st-amb->dir].frst=2;
    if(!cz->dir) broadcast(&empty);
    while((amb->dir==1)? cz->dir<0 : cz->dir>0) wait(&empty, &bridge_mutex), DEBUG(id++);
    if(amb->dir==cz->sem) (amb->dir==1)? cz->t1-- : cz->t2--;
    cz->dir+=amb->dir; --cz->amb_waiting;
    CrossBridge(amb, st, end, 2);
    cz->dir-=amb->dir; cz->bridge[end].frst=0;
    if(!cz->dir) broadcast(&empty);
    unlock(&cz->bridge[end].scnd);
    free(amb);
    return 0;
}

void* TrafficCarGenerator(double mu, double l, double u, double p, int d){
    while(1){
        zzz(-mu*log(1-prob())*micro);
        thread t;
        create(&t, (prob()<p)? CrossTrafficAmbulance : CrossTrafficCar, CreateCar(l, u, p, d));
        detach(t);
    }
}

void* run_generator_Traffic(void* arg) {
    domain* dom = (domain*)arg;
    TrafficCarGenerator(dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}
