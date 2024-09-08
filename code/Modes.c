#include "Car.h"
#include "UI/UI.c"
#include "Carnage/Carnage.c"
#include "Semaphore/Semaphore.c"
#include "Traffic/Traffic.c"
#include "util.h"

int mode, sz, k_i, k_j;
double mu_i, mu_j, t_si, t_sj, lbv_i, ubv_i, lbv_j, ubv_j, p_i, p_j;
Bridge *cz;
cond empty = INIT_COND;
mutex bridge_mutex = INIT_MUTEX;

void Carnage() {
    cz = init(sz);
    thread threads[3];
    domain lft = {1, mu_i, lbv_i, ubv_i, p_i}, rght = {-1, mu_j, lbv_j, ubv_j, p_j};
    create(&threads[0], run_generator_Carnage, &lft);
    create(&threads[1], run_generator_Carnage, &rght);
    create(&threads[2], UICarnage, cz);
    for (int i = 0; i < 3; i++) join(threads[i]);
}

void Semaphore() {
    cz = init(sz);
    thread threads[4];
    domain lft = {1, mu_i, lbv_i, ubv_i, p_i}, rght = {-1, mu_j, lbv_j, ubv_j, p_j};
    create(&threads[0], run_Semaphore, 0);
    create(&threads[1], run_generator_Semaphore, &lft);
    create(&threads[2], run_generator_Semaphore, &rght);
    create(&threads[3], UISemaphore, cz);
    for (int i = 0; i < 4; i++) join(threads[i]);
}

void Traffic() {
    cz = init(sz);
    thread threads[4];
    domain lft = {1, mu_i, lbv_i, ubv_i, p_i}, rght = {-1, mu_j, lbv_j, ubv_j, p_j};
    create(&threads[0], run_Traffic, 0);
    create(&threads[1], run_generator_Traffic, &lft);
    create(&threads[2], run_generator_Traffic, &rght);
    create(&threads[3], UITraffic, cz);
    for (int i = 0; i < 4; i++) join(threads[i]);
}
