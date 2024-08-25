#include "util.h"

typedef struct{
    double v; //Cars velocity, and time till spawn
    int ambulance;
} Car;

Car *CreateCar(double l, double u, double p){
    Car * c = (Car*)malloc(sizeof(Car));
    c->v = rrand(l, u);
    c->ambulance = prob()<p;
    printf("%d\n", c->ambulance);
    return c;
}

void* CrossBridge(void *arg){
    Car* car = (Car*)arg;
    if(car->ambulance) puts("ambulance is crossing the bridge!");
    else puts("car is crossing the brige!");
    return 0;
}
