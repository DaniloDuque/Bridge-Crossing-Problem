#include "Modes.c"

int main() {
    srand48(time(0));
    scanf("%d%d", &mode, &sz);
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &mu_i, &mu_j, &lbv_i, &ubv_i, &lbv_j, &ubv_j, &ambProb_i, &ambProb_j);
    if (mode == 1) scanf("%d%d", &k_i, &k_j);
    if (mode == 2) scanf("%lf%lf", &t_si, &t_sj);
    (!mode)? Carnage() : (mode==1)? Semaphore() : Traffic();
    return 0;
}
