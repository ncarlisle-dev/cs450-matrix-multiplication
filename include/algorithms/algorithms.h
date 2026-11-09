#pragma once
#include <matrix.h>
#include <assert.h>

typedef void (*mma_callback_t)(
    const mat_t* const,
    const mat_t* const,
    const mat_t* const,
    const unsigned short
);

/** A matrix multiplication algorithm. */
typedef enum
{
    MMA_INVALID = -1,
    MMA_NAIVE_IJK = 0,
    MMA_NAIVE_IKJ,
    MMA_NAIVE_JIK,
    MMA_NAIVE_JKI,
    MMA_NAIVE_KIJ,
    MMA_NAIVE_KJI,
    NUM_MMAS,
} mma_t;

void mat_mult(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const mma_t algorithm,
    const unsigned short num_threads
);
