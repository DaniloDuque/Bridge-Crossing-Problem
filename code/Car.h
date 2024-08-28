#ifndef CAR_H
#define CAR_H

#include "util.h"

typedef struct{
    int dir;
    double v;
} Car;

typedef struct{
    int dir;
    double mu, lbv, ubv, ambProb;
} domain;

Car * CreateCar(double l, double u, double p, int d){
    Car * c = (Car*)malloc(sizeof(Car));
    c->v = rrand(l, u);
    c->dir = d;
    return c;
}


#endif // !CAR_H
