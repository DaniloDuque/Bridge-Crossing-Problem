#include "Car.c"

typedef struct{

    void (*init)(double, double, double, double);

} CarGenerator;


void initCarMaker(double m, double l, double u, double p){

}

void create(CarGenerator &cg){
    cg->init = initCarMaker; 
}


