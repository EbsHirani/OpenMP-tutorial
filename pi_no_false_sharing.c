#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
int thread_count = 4;
double step;
int main(){
    double pi, sum = 0.0;
    double global_sum;
    step = 1.0/(double)num_steps;
    #pragma omp parallel num_threads(thread_count)
    {
        int id = omp_get_thread_num();
        int i;
        int nthreads = omp_get_num_threads();
        double x;
        double sum = 0.0;
        int start = id * (num_steps/nthreads);
        int end = start + (num_steps/nthreads);
        if (id == 0) thread_count = nthreads;
        // printf("%f\n", sums[id]);
        for (i = start; i < end; i++){
            x = (i+0.5) * step;
            sum = sum + 4.0/(1.0 + x*x);
        }
        
        #pragma omp atomic
            global_sum+=sum;

        // printf("start: %d, end: %d, id: %d, sum %d\n", start, end, id, sums[id]);
    }
    pi = step*global_sum;
    printf("Pi: %f", pi);
}