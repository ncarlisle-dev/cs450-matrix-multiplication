#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <matrix.h>
#include <algorithms/algorithms.h>
#include <cmdline.h>

int main(int argc, char* argv[])
{
    // get command line args
    cmdline_args_t args;
    const char* const msg = cmdline_get_args(
        argc,
        (const char* const * const)argv,
        &args
    );

    if (msg != NULL)
    {
        fprintf(stderr, "%s\n", msg);
        return 1;
    }

    // seed RNG
    srand((unsigned int)time(NULL));

    // begin benchmark
    // Time and print statements are for debugging

    // clock_t total_time = 0;
    mat_t* mat1    = mat_create(args.mat_size);
    mat_t* mat2    = mat_create(args.mat_size);
    mat_t* product = mat_create(args.mat_size);

    for (int i = 0; i < args.num_multiplications; i++)
    {
        mat_randomize(mat1);
        mat_randomize(mat2);

        // printf("Mat1 = \n");
        // mat_print(mat1);
        // printf("\nMat2 = \n");
        // mat_print(mat2);

        // const clock_t start_time = clock();
        mat_mult(mat1, mat2, product, args.mult_algo, args.num_threads);
        // const clock_t end_time = clock();

        // printf("\nProduct = \n");
        // mat_print(product);
        // printf("\n");
        
        // total_time += end_time - start_time;
    }

    // report times
    // double total_time_seconds = ((double)(total_time)) / CLOCKS_PER_SEC;
    // double average_time_seconds = total_time_seconds / NUM_MULTIPLICATIONS;

    // printf("Total time:   %lf\n", total_time_seconds);
    // printf("Average time: %lf\n", average_time_seconds);

    // cleanup
    mat_delete(&mat1);
    mat_delete(&mat2);
    mat_delete(&product);

    // return
	return 0;
}
