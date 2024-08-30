#include "Car.h"
#include "Bridge.h"

extern Bridge* cz;
pthread_mutex_t bridge_mutex;  
pthread_cond_t empty;  

void* CrossCarnageCar(void *arg){
    Car* car = (Car*)arg;
    int st = start(car), end = end(car);
    lock(&cz->bridge[st-car->dir].scnd); 
    while(cz->amb_waiting || ((car->dir == 1)? cz->dir<0 : cz->dir>0)) wait(&empty, &cz->bridge[st-car->dir].scnd);
    cz->dir += car->dir;  
    CrossBridge(car, st, end, 1);
    cz->dir -= car->dir; cz->bridge[end].frst=0;  
    if (cz->dir == 0) signal(&empty);
    unlock(&cz->bridge[end].scnd);
    return 0;
}

void* CarnageCarGenerator(double mu, double l, double u, double p, int d){
    while(1){
        usleep(-mu*log(1-prob())*micro);
        pthread_t t;
        pthread_create(&t, 0, (prob()<p)? CrossAmbulance : CrossCarnageCar, (void*)CreateCar(l, u, p, d));
        pthread_detach(t);
    }
}

void* run_generator_Carnage(void* arg) {
    domain* dom = (domain*)arg;
    CarnageCarGenerator(dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}
