#include "util.h"

int mode, sz, k_i, k_j;
double mu, t_si, t_sj, lbv, upv, ambProb;

int main(){

    scanf("%d %d %Lf %Lf %Lf %Lf", &mode, &sz, &mu, &lbv, &upv, &ambProb);
    if(mode==1) scanf("%d %d", &k_i, &k_j);
    if(mode==2) scanf("%Lf %Lf", &t_si, &t_sj);
    (!mode)? Carnage() : (mode==1)? Semaphore() : Traffic();
    return 0;

}
