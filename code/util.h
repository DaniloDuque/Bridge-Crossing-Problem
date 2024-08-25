#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>  
#include <time.h>
#include <math.h> 


#define prob() ((double)rand()/(RAND_MAX+1))
#define rrand(i, j) ((i)+prob()*((j)-(i)))

#endif 

