#include <omp.h>
#include <stdio.h>

int main()
{
	omp_set_num_threads(10);

    int i;
    #pragma omp for private(i) schedule(static)
    for (i = 0; i < 10; i++) {
		int tid = omp_get_thread_num();
		printf("Hello world from thread %d\n",tid);
    }

	return 0;
}
