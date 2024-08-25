#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>  
#include <time.h>
#include <math.h> 
#include <stdbool.h>

#define prob() ((double)rand()/(RAND_MAX))
#define rrand(i, j) ((i)+prob()*((j)-(i)))

#endif 

