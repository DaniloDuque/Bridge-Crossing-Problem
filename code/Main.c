#include "Modes.c"

int main() {

    srand48(time(0));
    printf("Select Mode (0 for Carnage, 1 for Semaphore, 2 for Traffic Officer): ");
    scanf("%d", &mode);
    printf("Enter the size of the bridge (positive integer): ");
    scanf("%d", &sz);
    puts("Enter the average car spawn time in seconds (positive real number):");
    printf("Left side: "); scanf("%lf", &mu_i); 
    printf("Right side: "); scanf("%lf", &mu_j); 
    puts("Enter the velocity range of cars (positive real numbers):");
    printf("Left side (lower bound and upper bound): "); scanf("%lf%lf", &lbv_i, &ubv_i); 
    printf("Right side (lower bound and upper bound): "); scanf("%lf%lf", &lbv_j, &ubv_j); 
    puts("Enter the probability of an ambulance appearing (real number in [0, 1]):");
    printf("Left side: "); scanf("%lf", &p_i);
    printf("Right side: "); scanf("%lf", &p_j);

    if (mode == 1) {
        puts("Enter the duration of the semaphore in seconds (positive real number):");
        printf("Left side: "); scanf("%lf", &t_si);
        printf("Right side: "); scanf("%lf", &t_sj);
    }

    if (mode == 2) {
        puts("Enter the number of cars allowed to pass per round (positive integer):");
        printf("Left side: "); scanf("%d", &k_i);
        printf("Right side: "); scanf("%d", &k_j);
    }

    (!mode) ? Carnage() : (mode == 1) ? Semaphore() : Traffic();
    return 0;
}

