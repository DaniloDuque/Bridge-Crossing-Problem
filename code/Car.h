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

#endif // !CAR_H
