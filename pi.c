#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
int thread_count = 4;
int pad = 8; // To avoid the sum array elements being on the same 64 byte cache line
double step;
int main(){
    double pi, sum = 0.0;
    double sums[thread_count][pad];
    step = 1.0/(double)num_steps;
    #pragma omp parallel num_threads(thread_count)
    {
        int id = omp_get_thread_num();
        int i;
        int nthreads = omp_get_num_threads();
        double x;
        sums[id][0] = 0.0;
        int start = id * (num_steps/nthreads);
        int end = start + (num_steps/nthreads);
        if (id == 0) thread_count = nthreads;
        // printf("%f\n", sums[id]);
        for (i = start; i < end; i++){
            x = (i+0.5) * step;
            sums[id][0] = sums[id][0] + 4.0/(1.0 + x*x);
        }
        // printf("start: %d, end: %d, id: %d, sum %d\n", start, end, id, sums[id]);
    }
    for (int i = 0; i < thread_count; i++) sum += sums[i][0];
    pi = step*sum;
    printf("Pi: %f", pi);
}