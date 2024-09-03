#include "Car.h"
#include "Bridge.h"

extern Bridge* cz;
cond empty;
mutex bridge_mutex;
extern int k_i, k_j;

void *run_Traffic() {
    while (1) {
        lock(&bridge_mutex);
        cz->sem = 1, cz->t1 = k_i, cz->t2=0;
        while((cz->amb_waiting || (cz->t1>0))){
            if(!cz->dir && !cz->amb_waiting && !cz->bridge[0].frst && cz->bridge[cz->sz+1].frst) break;
            wait(&empty, &bridge_mutex);
        }cz->sem = -1, cz->t2 = k_j, cz->t1=0;
        while((cz->amb_waiting || (cz->t2>0))) {
            if(!cz->dir && !cz->amb_waiting && cz->bridge[0].frst && !cz->bridge[cz->sz+1].frst) break;
            wait(&empty, &bridge_mutex);
        }unlock(&bridge_mutex);
    }
}

void* CrossTrafficCar(void *arg) {
    Car* car = (Car*)arg;
    int st = start(car), end = end(car);
    lock(&cz->bridge[st-car->dir].scnd); 
    cz->bridge[st-car->dir].frst=1; 
    while(cz->amb_waiting || ((car->dir == 1)? cz->dir<0 : cz->dir>0) || (car->dir != cz->sem)) wait(&empty, &bridge_mutex);
    (car->dir == 1)? --cz->t1 : --cz->t2;
    cz->dir += car->dir;
    CrossBridge(car, st, end, 1);
    cz->dir -= car->dir;
    cz->bridge[end].frst = 0;
    if (cz->dir == 0) signal(&empty);
    unlock(&cz->bridge[end].scnd);
    free(car);
    return 0;
}

void *CrossTrafficAmbulance(void *arg){
    Car* amb = (Car*)arg;
    int st = start(amb), end = end(amb);
    lock(&cz->bridge[st-amb->dir].scnd); ++cz->amb_waiting; 
    cz->bridge[st-amb->dir].frst=2;
    while((amb->dir==1)? cz->dir<0 : cz->dir>0) wait(&empty, &cz->bridge[st-amb->dir].scnd);
    if(amb->dir == cz->sem) (amb->dir==1)? --cz->t1 : --cz->t2;
    cz->dir+=amb->dir; --cz->amb_waiting;
    CrossBridge(amb, st, end, 2);
    cz->dir-=amb->dir; cz->bridge[end].frst=0;
    if(cz->dir==0) signal(&empty);
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
