#include "CarGenerator.c"
#include "UI.c"

int mode, sz, k_i, k_j;
double mu_i, mu_j, t_si, t_sj, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j;

void initUI(){pthread_t t; pthread_create(&t, NULL, print, (void*)cz); pthread_detach(t);}

void Carnage() {
    INIT(sz, mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
    initUI();
    
}

void Semaphore() {
    INIT(sz, mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
    initUI();
}

void Traffic() {
    INIT(sz, mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
    initUI();
}


