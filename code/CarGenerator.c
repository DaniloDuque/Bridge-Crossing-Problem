#include "Car.h"
#include "UI.c"
#include "Bridge.h"

Bridge* cz;
int id = 1;
pthread_mutex_t bridge_mutex;  
pthread_cond_t empty;  

typedef struct{
    int dir;
    double mu, lbv, ubv, ambProb;
} domain;

void* CrossBridge(void *arg){
    Car* car = (Car*)arg;
    int start = (car->dir == 1) ? 1 : cz->sz;
    int end = (start == 1) ? cz->sz : 1;
    pthread_mutex_lock(&bridge_mutex);
    while ((car->dir == 1) ? cz->dir < 0 : cz->dir > 0) pthread_cond_wait(&empty, &bridge_mutex);
    cz->dir += car->dir;  
    pthread_mutex_unlock(&bridge_mutex);
    for (int i = start; i != end + car->dir; i += car->dir) {
        pthread_mutex_lock(&cz->bridge[i].scnd);
        cz->bridge[i - car->dir].frst = 0;
        pthread_mutex_unlock(&cz->bridge[i - car->dir].scnd);
        cz->bridge[i].frst = car->id;
        usleep(1 * micro / car->v);
    }pthread_mutex_lock(&bridge_mutex);
    cz->dir -= car->dir; cz->bridge[end].frst=0;  
    if (cz->dir == 0) pthread_cond_broadcast(&empty);
    pthread_mutex_unlock(&bridge_mutex);
    pthread_mutex_unlock(&cz->bridge[end].scnd);
    return 0;
}

void CreateCar(double l, double u, double p, int d){
    Car * c = (Car*)malloc(sizeof(Car));
    c->v = rrand(l, u);
    c->id = id++;
    c->ambulance = prob()<p;
    c->dir = d;
    pthread_t t;
    pthread_create(&t, NULL, CrossBridge, (void*)c);
    pthread_detach(t);
}

void* CarGenerator(double mu, double l, double u, double p, int d){
    while(1){
        usleep(-mu*log(1-prob())*micro);
        CreateCar(l, u, p, d);
   }
}

void* run_car_generator(void* arg) {
    domain* dom = (domain*)arg;
    CarGenerator(dom->mu, dom->lbv, dom->ubv, dom->ambProb, dom->dir);
    return 0;
}

void INIT(int sz, double m_i, double m_j, double l_i, double u_i, double l_j, double u_j , double p_i, double p_j) {
    cz = init(sz);
    pthread_t threads[3];
    domain lft = {1, m_i, l_i, u_i, p_i}, rght = {-1, m_j, l_j, u_j, p_j};
    pthread_create(&threads[0], NULL, run_car_generator, (void*)&lft);
    pthread_create(&threads[1], NULL, run_car_generator, (void*)&rght);
    pthread_create(&threads[2], NULL, print, (void*)cz);
    for (int i = 0; i < 3; i++) pthread_join(threads[i], NULL);
}
