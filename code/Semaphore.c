#include "Car.h"
#include "Bridge.h"
#include "util.h"

extern Bridge* cz;
extern mutex bridge_mutex;
mutex safe = INIT_MUTEX;  
extern cond empty;
cond change_semaphore = INIT_COND;  
extern double t_si, t_sj;

void *run_Semaphore(){
    while(1){
        cz->sem = 1;
        signal(&change_semaphore);
        zzz(t_si*micro);
        cz->sem = -1;
        signal(&change_semaphore);
        zzz(t_sj*micro);
    }
}

void* CrossSemaphoreCar(void *arg){
    Car* car = (Car*)arg;
    int st = start(car), end = end(car);
    lock(&cz->bridge[st-car->dir].scnd); 
    if(cz->sem != car->dir) wait(&change_semaphore, &safe);
    lock(&bridge_mutex); 
    cz->bridge[st-car->dir].frst=1;
    while(cz->amb_waiting || ((car->dir==1)? cz->dir<0 : cz->dir>0) || (car->dir != cz->sem)) wait(&empty, &bridge_mutex);
    cz->dir += car->dir;  
    unlock(&bridge_mutex);
    CrossBridge(car, st, end, 1);
    cz->dir -= car->dir;
    cz->bridge[end].frst = 0;  
    if(cz->dir == 0) signal(&empty);
    unlock(&cz->bridge[end].scnd); 
    free(car);
    return 0;
}

void* SemaphoreCarGenerator(double mu, double l, double u, double p, int d){
    while(1){
        zzz(-mu*log(1-prob())*micro);
        thread t;
        create(&t, (prob()<p)? CrossAmbulance : CrossSemaphoreCar, CreateCar(l, u, p, d));
        detach(t);
    }
}

void* run_generator_Semaphore(void* arg) {
    domain* dom = (domain*)arg;
    SemaphoreCarGenerator(dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}
