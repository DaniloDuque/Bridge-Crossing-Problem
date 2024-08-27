#include "Car.h"
#include "Bridge.h"

Bridge* cz;

typedef struct{
    int id, dir;
    double mu;
    double lbv;
    double ubv;
    double ambProb;
} domain;

void* CrossBridge(void *arg){
    Car* car = (Car*)arg;
    pthread_mutex_lock(&cz->bridge[(car->dir == 1)? 0 : cz->sz+1].scnd);
    for(int i = (car->dir == 1)? 1 : cz->sz; (car->dir == 1)? i<=cz->sz : i>=1; i+=car->dir){
        pthread_mutex_lock(&cz->bridge[i].scnd);
        sleep(1/car->v);
        if(i == ((car->dir == 1)? cz->sz : 1)) pthread_mutex_lock(&cz->bridge[i+car->dir].scnd);
        pthread_mutex_unlock(&cz->bridge[i].scnd);
    }return 0;
}

void CreateCar(double l, double u, double p, int d){
    Car * c = (Car*)malloc(sizeof(Car));
    c->v = rrand(l, u);
    c->ambulance = prob()<p;
    c->dir = d;
    pthread_t t;
    pthread_create(&t, NULL, CrossBridge, (void*)c);
    pthread_detach(t);
}

void* CarGenerator(int id, double mu, double l, double u, double p, int d){
    while(1){
        double w = -mu*log(1-prob());
        printf("id:%d %lf\n", id, w);
        sleep(w);
        CreateCar(l, u, p, d);
   }
}

void* run_car_generator(void* arg) {
    domain* dom = (domain*)arg;
    CarGenerator(dom->id, dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}

void INIT(int sz, double m_i, double m_j, double l_i, double u_i, double l_j, double u_j , double p_i, double p_j) {
    cz = init(sz);
    pthread_t threads[2];
    domain lft = {0, m_i, l_i, u_i, p_i, 1}, rght = {1, m_j, l_j, u_j, p_j, -1};
    pthread_create(&threads[0], NULL, run_car_generator, (void*)&lft);
    pthread_create(&threads[1], NULL, run_car_generator, (void*)&rght);
    for (int i = 0; i < 2; i++) pthread_join(threads[i], NULL);
}
