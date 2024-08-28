#include "Car.h"
#include "Bridge.h"

extern Bridge* cz;
pthread_mutex_t bridge_mutex;  
pthread_cond_t empty;  

void *CrossTrafficAmbulance(void *arg){
    Car* amb = (Car*)arg;
    int start = (amb->dir==1)? 1 : cz->sz, end = (start==1)? cz->sz : 1;
    lock(&cz->bridge[start-amb->dir].scnd); lock(&bridge_mutex); ++cz->amb_waiting;
    while((amb->dir == 1) ? cz->dir < 0 : cz->dir > 0) pthread_cond_wait(&empty, &bridge_mutex);
    cz->dir+=amb->dir; --cz->amb_waiting;
    unlock(&bridge_mutex);
    for(int i = start; i!=end+amb->dir; i+=amb->dir){
        lock(&cz->bridge[i].scnd);
        cz->bridge[i-amb->dir].frst=0;
        unlock(&cz->bridge[i-amb->dir].scnd);
        cz->bridge[i].frst=2;
        usleep(micro / amb->v);
    }lock(&bridge_mutex);
    cz->dir-=amb->dir; cz->bridge[end].frst=0;
    if(cz->dir == 0) pthread_cond_broadcast(&empty);
    unlock(&bridge_mutex); unlock(&cz->bridge[end].scnd);
    return 0;
}

void* CrossTrafficCar(void *arg){
    Car* car = (Car*)arg;
    int start = (car->dir==1)? 1 : cz->sz, end = (start==1)? cz->sz : 1;
    lock(&cz->bridge[start-car->dir].scnd); lock(&bridge_mutex); 
    while(cz->amb_waiting || (car->dir == 1) ? cz->dir < 0 : cz->dir > 0) pthread_cond_wait(&empty, &bridge_mutex);
    cz->dir += car->dir;  
    unlock(&bridge_mutex);
    for (int i = start; i!=end+car->dir; i += car->dir) {
        lock(&cz->bridge[i].scnd);
        cz->bridge[i - car->dir].frst = 0;
        unlock(&cz->bridge[i - car->dir].scnd);
        cz->bridge[i].frst = 1;
        usleep(micro / car->v);
    }lock(&bridge_mutex);
    cz->dir -= car->dir; cz->bridge[end].frst=0;  
    if (cz->dir == 0) pthread_cond_broadcast(&empty);
    unlock(&bridge_mutex); unlock(&cz->bridge[end].scnd);
    return 0;
}

void* TrafficCarGenerator(double mu, double l, double u, double p, int d){
    while(1){
        usleep(-mu*log(1-prob())*micro);
        pthread_t t;
        pthread_create(&t, 0, (prob()<p)? CrossTrafficAmbulance : CrossTrafficCar, (void*)CreateCar(l, u, p, d));
        pthread_detach(t);
    }
}

void* run_generator_Traffic(void* arg) {
    domain* dom = (domain*)arg;
    TrafficCarGenerator(dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}
