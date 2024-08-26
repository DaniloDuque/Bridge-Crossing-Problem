#include "util.h"

typedef struct{
    double v;
    int ambulance;
} Car;

Car *CreateCar(double l, double u, double p){
    Car * c = (Car*)malloc(sizeof(Car));
    c->v = rrand(l, u);
    c->ambulance = prob()<p;
    printf("%d\n", c->ambulance);
    return c;
}

