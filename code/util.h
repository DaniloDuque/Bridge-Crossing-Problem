#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>  
#include <time.h>
#include <math.h> 
#include <stdbool.h>
#include <unistd.h>

#define prob() (drand48())
#define rrand(i, j) ((i)+prob()*((j)-(i)))

#endif 

