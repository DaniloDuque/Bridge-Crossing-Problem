#include "CarGenerator.c"

int mode, sz, k_i, k_j;
double mu_i, mu_j, t_si, t_sj, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j;

void INIT(int sz, double m_i, double m_j, double l_i, double u_i, double l_j, double u_j , double p_i, double p_j) {
    cz = init(sz);
    pthread_t threads[3];
    domain lft = {1, m_i, l_i, u_i, p_i}, rght = {-1, m_j, l_j, u_j, p_j};
    pthread_create(&threads[0], 0, run_car_generator, (void*)&lft);
    pthread_create(&threads[1], 0, run_car_generator, (void*)&rght);
    pthread_create(&threads[2], 0, print, (void*)cz);
    for (int i = 0; i < 3; i++) pthread_join(threads[i], 0);
}

void Carnage() {
    INIT(sz, mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
}

void Semaphore() {
    INIT(sz, mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
}

void Traffic() {
    INIT(sz, mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
}


