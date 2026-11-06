#pragma once
#include <matrix.h>
#include <algorithms/algorithms.h>

typedef struct
{
    mat_size_t     mat_size;
    mma_t          mult_algo;
    unsigned short num_threads;
    unsigned short num_multiplications;
} cmdline_args_t;

char* cmdline_get_args(
    const int argc,
    const char* const argv[],
    cmdline_args_t* const args
);
