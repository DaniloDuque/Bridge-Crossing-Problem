#include "util.h"

typedef struct{
    double v, w; //Cars velocity, and time till spawn
    int ambulance;
} Car;

void init(Car *car, double mu, double lbv, double upv, double ambProb){
    car->v = rrand(lbv, upv);
    car->ambulance = (prob()<ambProb);
}
