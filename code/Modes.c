#include "UI.c"
#include "Carnage.c"
#include "Semaphore.c"
#include "Traffic.c"

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
    cz = init(sz);
    pthread_t threads[4];
    domain lft = {1, mu_i, lbv_i, ubv_i, p_i}, rght = {-1, mu_j, lbv_j, ubv_j, p_j};
    pthread_create(&threads[0], 0, Run_Semaphore, 0);
    pthread_create(&threads[1], 0, run_generator_Semaphore, (void*)&lft);
    pthread_create(&threads[2], 0, run_generator_Semaphore, (void*)&rght);
    pthread_create(&threads[3], 0, UISemaphore, (void*)cz);
    for (int i = 0; i < 4; i++) pthread_join(threads[i], 0);
}

void Traffic() {
    cz = init(sz);
    pthread_t threads[4];
    domain lft = {1, mu_i, lbv_i, ubv_i, p_i}, rght = {-1, mu_j, lbv_j, ubv_j, p_j};
    //pthread_create(&threads[0], 0, Run_Traffic, 0);
    //pthread_join(threads[0], 0);
    pthread_create(&threads[1], 0, run_generator_Traffic, (void*)&lft);
    pthread_create(&threads[2], 0, run_generator_Traffic, (void*)&rght);
    pthread_create(&threads[3], 0, UITraffic, (void*)cz);
    for (int i = 1; i < 4; i++) pthread_join(threads[i], 0);
}
