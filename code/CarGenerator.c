#include "Car.c"

typedef struct{
    int id;
    double mu;
    double lbv;
    double ubv;
    double ambProb;
} domain;

void* CarGenerator(int id, double mu, double l, double u, double p){
    while(1){
        double w = -mu*log(1-prob());
        printf("id:%d %lf\n", id, w);
        sleep(w);
    }
}
