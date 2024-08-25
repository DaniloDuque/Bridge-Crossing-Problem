#include "CarGenerator.c" 

int mode, sz, k_i, k_j;
double mu, t_si, t_sj, lbv, upv, ambProb;

void* run_car_generator(void* arg) {
    domain* params = (domain*)arg;
    CarGenerator(params->mu, params->lbv, params->upv, params->ambProb);
    return NULL;
}

void INIT(double m, double l, double u, double p) {
    pthread_t threads[2];
    domain params = {m, l, u, p};
    for (int i = 0; i < 2; i++)
        if (pthread_create(&threads[i], NULL, run_car_generator, (void*)&params) != 0) {
            fprintf(stderr, "Failed to create thread\n");
            exit(EXIT_FAILURE);
        }
    for (int i = 0; i < 2; i++) pthread_join(threads[i], NULL);
}

void Carnage() {
    INIT(mu, lbv, upv, ambProb);
}

void Semaphore() {
    INIT(mu, lbv, upv, ambProb);
}

void Traffic() {
    INIT(mu, lbv, upv, ambProb);
}

int main() {
    srand48(time(0));
    scanf("%d%d%lf%lf%lf%lf", &mode, &sz, &mu, &lbv, &upv, &ambProb);
    if (mode == 1) scanf("%d%d", &k_i, &k_j);
    if (mode == 2) scanf("%lf%lf", &t_si, &t_sj);
    (!mode)? Carnage() : (mode==1)? Semaphore() : Traffic();
    return 0;
}

