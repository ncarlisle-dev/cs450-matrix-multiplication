#pragma once
#include <matrix.h>

void mat_mult_openblas(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
);
