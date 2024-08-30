#include "Car.h"
#include "Bridge.h"

extern Bridge* cz;
pthread_mutex_t bridge_mutex;  
pthread_cond_t empty;  

void* CrossTrafficCar(void *arg){
    Car* car = (Car*)arg;
    int start = (car->dir==1)? 1 : cz->sz, end = (start==1)? cz->sz : 1;
    lock(&cz->bridge[start-car->dir].scnd); lock(&bridge_mutex); 
    while(cz->amb_waiting || ((car->dir == 1) ? cz->dir < 0 : cz->dir > 0)) pthread_cond_wait(&empty, &bridge_mutex);
    cz->dir += car->dir;  
    unlock(&bridge_mutex);
    CrossBridge(car, start, end, 1);
    lock(&bridge_mutex);
    cz->dir -= car->dir; cz->bridge[end].frst=0;  
    if (cz->dir == 0) pthread_cond_broadcast(&empty);
    unlock(&bridge_mutex); unlock(&cz->bridge[end].scnd);
    return 0;
}

void* TrafficCarGenerator(double mu, double l, double u, double p, int d){
    while(1){
        usleep(-mu*log(1-prob())*micro);
        pthread_t t;
        pthread_create(&t, 0, (prob()<p)? CrossAmbulance : CrossTrafficCar, (void*)CreateCar(l, u, p, d));
        pthread_detach(t);
    }
}

void* run_generator_Traffic(void* arg) {
    domain* dom = (domain*)arg;
    TrafficCarGenerator(dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}
