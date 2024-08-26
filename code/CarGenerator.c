#include "Car.c"
#include "Bridge.c"

Bridge* cz;

typedef struct{
    int id;
    double mu;
    double lbv;
    double ubv;
    double ambProb;
} domain;

void* CrossBridge(void *arg){
    Car* car = (Car*)arg;
    for(int i = 0; i<cz->sz; ++i){
        pthread_mutex_lock(&cz->bridge[i]);
        printf("%d ", i), sleep(car->v);
        pthread_mutex_unlock(&cz->bridge[i]);
    }
    return 0;
}

void* CarGenerator(int id, double mu, double l, double u, double p){
    while(1){
        double w = -mu*log(1-prob());
        printf("id:%d %lf\n", id, w);
        sleep(w);
        Car * new = CreateCar(l, u, p);
        pthread_t t;
        pthread_create(&t, NULL, CrossBridge, (void*)new);
        pthread_detach(t);
    }
}

void* run_car_generator(void* arg) {
    domain* dom = (domain*)arg;
    CarGenerator(dom->id, dom->mu, dom->lbv, dom->ubv, dom->ambProb);
    return NULL;
}

void INIT(int sz, double m_i, double m_j, double l_i, double u_i, double l_j, double u_j , double p_i, double p_j) {
    cz = init(sz);
    pthread_t threads[2];
    domain lft = {0, m_i, l_i, u_i, p_i}, rght = {1, m_j, l_j, u_j, p_j};
    pthread_create(&threads[0], NULL, run_car_generator, (void*)&lft);
    pthread_create(&threads[1], NULL, run_car_generator, (void*)&rght);
    for (int i = 0; i < 2; i++) pthread_join(threads[i], NULL);
}

