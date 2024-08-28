#include "UI.c"
#include "Carnage.c"
#include "Semaphore.c"

int mode, sz, k_i, k_j;
double mu_i, mu_j, t_si, t_sj, lbv_i, ubv_i, lbv_j, ubv_j, p_i, p_j;
Bridge *cz;

void Carnage() {
    cz = init(sz);
    pthread_t threads[3];
    domain lft = {1, mu_i, lbv_i, ubv_i, p_i}, rght = {-1, mu_j, lbv_j, ubv_j, p_j};
    pthread_create(&threads[0], 0, run_generator_Carnage, (void*)&lft);
    pthread_create(&threads[1], 0, run_generator_Carnage, (void*)&rght);
    pthread_create(&threads[2], 0, UICarnage, (void*)cz);
    for (int i = 0; i < 3; i++) pthread_join(threads[i], 0);
}

void Semaphore() {
}

void Traffic() {
}
