#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
int thread_count = 4;
int pad = 8; // To avoid the sum array elements being on the same 64 byte cache line
double step;
int main(){
    double pi, sum = 0.0;
    step = 1.0/(double)num_steps;
    omp_set_num_threads(thread_count);
    #pragma omp parallel for reduction (+:sum)
        for (int i = 0; i < num_steps; i++){
            double x = (i+0.5) * step;
            sum += 4.0/(1.0 + x*x);
        }    
    pi = step*sum;
    printf("Pi: %f", pi);
}