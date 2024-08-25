#include "CarGenerator.c"
#include "CarGenerator.h"

int mode, sz, k_i, k_j;
double mu, t_si, t_sj, lbv, upv, ambProb;

void INIT(double m, double l, double u, double p){
    void *ps = {m, l, u, p};
    pthread_create(&thread, NULL, CarGenerator, &ps);
    pthread_create(&thread, NULL, CarGenerator, &ps);
}

void Carnage(){
    INIT(mu, lbv, upv, ambProb);

}

void Semaphore(){
    INIT(mu, lbv, upv, ambProb);

}

void Traffic(){
    INIT(mu, lbv, upv, ambProb);

}

int main(){

    srand48(time(0));
    scanf("%d%d%lf%lf%lf%lf", &mode, &sz, &mu, &lbv, &upv, &ambProb);
    if(mode==1) scanf("%d%d", &k_i, &k_j);
    if(mode==2) scanf("%lf%lf", &t_si, &t_sj);
    (!mode)? Carnage() : (mode==1)? Semaphore() : Traffic();
    return 0;

}
