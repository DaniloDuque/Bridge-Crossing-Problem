#include "Car.h"
#include "UI.c"
#include "Bridge.h"
#include "util.h"

Bridge* cz;
pthread_mutex_t bridge_mutex;  
pthread_cond_t empty;  
int amb_waiting = 0;

void *CrossBridgeAmbulance(void *arg){
    Car* amb = (Car*)arg;
    int start = (amb->dir==1)? 1 : cz->sz, end = (start==1)? cz->sz : 1;
    lock(&cz->bridge[start-amb->dir].scnd); lock(&bridge_mutex); ++amb_waiting;
    while((amb->dir == 1) ? cz->dir < 0 : cz->dir > 0) pthread_cond_wait(&empty, &bridge_mutex);
    cz->dir+=amb->dir; --amb_waiting;
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

void* CrossBridgeCar(void *arg){
    Car* car = (Car*)arg;
    int start = (car->dir==1)? 1 : cz->sz, end = (start==1)? cz->sz : 1;
    lock(&cz->bridge[start-car->dir].scnd); lock(&bridge_mutex); 
    while(amb_waiting || (car->dir == 1) ? cz->dir < 0 : cz->dir > 0) pthread_cond_wait(&empty, &bridge_mutex);
    cz->dir += car->dir;  
    unlock(&bridge_mutex);
    for (int i = start; i!=end+car->dir; i += car->dir) {
        lock(&cz->bridge[i].scnd);
        cz->bridge[i - car->dir].frst = 0;
        unlock(&cz->bridge[i - car->dir].scnd);
        cz->bridge[i].frst = 1;
        usleep(1 * micro / car->v);
    }lock(&bridge_mutex);
    cz->dir -= car->dir; cz->bridge[end].frst=0;  
    if (cz->dir == 0) pthread_cond_broadcast(&empty);
    unlock(&bridge_mutex); unlock(&cz->bridge[end].scnd);
    return 0;
}

void CreateCar(double l, double u, double p, int d){
    Car * c = (Car*)malloc(sizeof(Car));
    c->v = rrand(l, u);
    c->dir = d;
    pthread_t t;
    pthread_create(&t, 0, (prob()<p)? CrossBridgeAmbulance : CrossBridgeCar, (void*)c);
    pthread_detach(t);
}

void* CarGenerator(double mu, double l, double u, double p, int d){
    while(1){
        usleep(-mu*log(1-prob())*micro);
        CreateCar(l, u, p, d);
   }
}

void* run_car_generator(void* arg) {
    domain* dom = (domain*)arg;
    CarGenerator(dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}
