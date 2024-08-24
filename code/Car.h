#include "util.h"


struct Car{
    
    double v, w; //Cars velocity, and time till spawn
    bool ambulance;

    void init(double mu, double lbv, double upv, double ambProb){
        w = -mu*log(1-prob());
        v = rrand(lbv, upv);
        ambulance = (prob()<ambProb);
    }

};
