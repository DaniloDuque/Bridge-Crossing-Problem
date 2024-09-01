#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>  
#include <time.h>
#include <math.h> 
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>

#define prob() (drand48())
#define rrand(i, j) ((i)+prob()*((j)-(i)))
#define micro 1000000
#define lock(x) (pthread_mutex_lock(x))
#define unlock(x) (pthread_mutex_unlock(x))
#define wait(c, m) (pthread_cond_wait(c, m))
#define signal(x) (pthread_cond_signal(x))
#define broadcast(x) (pthread_cond_broadcast(x))
#define RED "\x1b[41m"  
#define GREEN "\x1b[42m" 
#define COLOR_RESET "\x1b[0m"   
#define RED_CIRCLE "🔴"
#define GREEN_CIRCLE "🟢"
#define start(x) ((x->dir==1)? 1 : cz->sz)
#define end(x) ((x->dir==1)? cz->sz : 1)
#define DEBUG(x) (printf("%d\n", x))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define zzz(x) (usleep(x))


#endif 

