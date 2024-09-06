#include "Car.h"
#include "Bridge.h"
#include "util.h"

extern Bridge* cz;
extern mutex bridge_mutex;  
extern cond empty;    

void* EnterCarnageCar(void *arg) {
    Car* car = (Car*)arg;
    int st = start(car), end = end(car);
    lock(&cz->bridge[st-car->dir].scnd); lock(&bridge_mutex);  
    cz->bridge[st-car->dir].frst = 1;
    while(cz->amb_waiting || ((car->dir == 1) ? cz->dir < 0 : cz->dir > 0)) wait(&empty, &bridge_mutex);
    cz->dir += car->dir; unlock(&bridge_mutex);  
    CrossBridge(car, st, end, 1); 
    lock(&bridge_mutex);  
    cz->dir -= car->dir; cz->bridge[end].frst = 0;
    if(!cz->dir) signal(&empty);  
    unlock(&bridge_mutex); unlock(&cz->bridge[end].scnd);  
    free(car);  
    return 0;
}

void* CarnageCarGenerator(double mu, double l, double u, double p, int d){
    while(1){
        zzz(-mu*log(1-prob())*micro);
        thread t;
        create(&t, (prob()<p)? EnterAmbulance : EnterCarnageCar, CreateCar(l, u, p, d));
        detach(t);
    }
}

void* run_generator_Carnage(void* arg) {
    domain* dom = (domain*)arg;
    CarnageCarGenerator(dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}
