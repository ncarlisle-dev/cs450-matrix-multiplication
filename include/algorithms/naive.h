#pragma once
#include <matrix.h>

void mat_mult_naive_ijk(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
);

void mat_mult_naive_ikj(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
);

void mat_mult_naive_jik(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
);

void mat_mult_naive_jki(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
);

void mat_mult_naive_kji(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
);

void mat_mult_naive_kij(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
);
