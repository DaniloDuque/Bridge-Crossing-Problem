#include "Car.c"

typedef struct{
    double mu;
    double lbv;
    double upv;
    double ambProb;
} domain;

void* CarGenerator(double mu, double l, double u, double p){
    while(1){
        double w = -mu*log(1-prob());
        sleep(w);
        printf("%lf\n", w);
    }
}

