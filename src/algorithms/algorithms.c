#include <algorithms/algorithms.h>
#include <algorithms/naive.h>

static const mma_callback_t _MMA_CALLBACK_MAP[NUM_MMAS] = {
    [MMA_NAIVE_IJK] = mat_mult_naive_ijk,
    [MMA_NAIVE_IKJ] = mat_mult_naive_ikj,
    [MMA_NAIVE_JIK] = mat_mult_naive_jik,
    [MMA_NAIVE_JKI] = mat_mult_naive_jki,
    [MMA_NAIVE_KIJ] = mat_mult_naive_kij,
    [MMA_NAIVE_KJI] = mat_mult_naive_kji,
};

void mat_mult(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const mma_t algorithm,
    const unsigned short num_threads
)
{
    assert(algorithm != MMA_INVALID && algorithm != NUM_MMAS);
    assert(mat1->size == mat2->size);
    assert(mat1->size == product->size);

    _MMA_CALLBACK_MAP[algorithm](mat1, mat2, product, num_threads);
}
