#include "util.h"

int mode, sz, k_i, k_j;
double mu, t_si, t_sj, lbv, upv, ambProb;


void Carnage(){

}

void Semaphore(){

}

void Traffic(){

}

int main(){

    scanf("%d %d %lf %lf %lf %lf", &mode, &sz, &mu, &lbv, &upv, &ambProb);
    if(mode==1) scanf("%d %d", &k_i, &k_j);
    if(mode==2) scanf("%lf %lf", &t_si, &t_sj);
    (!mode)? Carnage() : (mode==1)? Semaphore() : Traffic();
    return 0;

}
