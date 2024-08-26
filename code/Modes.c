#include "CarGenerator.c"

int mode, sz, k_i, k_j;
double mu_i, mu_j, t_si, t_sj, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j;

void Carnage() {
    INIT(sz, mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
}

void Semaphore() {
    INIT(sz, mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
}

void Traffic() {
    INIT(sz, mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
}


