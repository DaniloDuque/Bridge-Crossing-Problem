#include "CarGenerator.c" 
#include <pthread.h>

int mode, sz, k_i, k_j;
double mu_i, mu_j, t_si, t_sj, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j;

void* run_car_generator(void* arg) {
    domain* dom = (domain*)arg;
    CarGenerator(dom->id, dom->mu, dom->lbv, dom->ubv, dom->ambProb);
    return NULL;
}

void INIT(double m_i, double m_j, double l_i, double u_i, double l_j, double u_j , double p_i, double p_j) {
    pthread_t threads[2];
    domain lft = {0, m_i, l_i, u_i, p_i}, rght = {1, m_j, l_j, u_j, p_j};
    pthread_create(&threads[0], NULL, run_car_generator, (void*)&lft);
    pthread_create(&threads[1], NULL, run_car_generator, (void*)&rght);
    for (int i = 0; i < 2; i++) pthread_join(threads[i], NULL);
}

void Carnage() {
    INIT(mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
}

void Semaphore() {
    INIT(mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
}

void Traffic() {
    INIT(mu_i, mu_j, lbv_i, ubv_i, lbv_j, ubv_j, ambProb_i, ambProb_j);
}

int main() {
    srand48(time(0));
    scanf("%d%d", &mode, &sz);
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &mu_i, &mu_j, &lbv_i, &ubv_i, &lbv_j, &ubv_j, &ambProb_i, &ambProb_j);
    if (mode == 1) scanf("%d%d", &k_i, &k_j);
    if (mode == 2) scanf("%lf%lf", &t_si, &t_sj);
    (!mode)? Carnage() : (mode==1)? Semaphore() : Traffic();
    return 0;
}
