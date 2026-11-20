#include <algorithms/algorithms.h>
#include <algorithms/naive.h>
#include <cblas.h>
#include <stdlib.h>
#include <string.h>

static void mat_mult_openblas(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
)
{
    const int n = mat1->size;
    const size_t row_bytes = (size_t)n * sizeof(mat_element_t);
    const size_t total_bytes = (size_t)n * row_bytes;

    mat_element_t* a = (mat_element_t*)malloc(total_bytes);
    mat_element_t* b = (mat_element_t*)malloc(total_bytes);
    mat_element_t* c = (mat_element_t*)malloc(total_bytes);

    for (int i = 0; i < n; i++)
    {
        memcpy(a + (size_t)i * n, mat1->data[i], row_bytes);
        memcpy(b + (size_t)i * n, mat2->data[i], row_bytes);
    }

    openblas_set_num_threads(num_threads);

    cblas_sgemm(
        CblasRowMajor, CblasNoTrans, CblasNoTrans,
        n, n, n,
        1.0f,
        a, n,
        b, n,
        0.0f,
        c, n
    );

    for (int i = 0; i < n; i++)
        memcpy(product->data[i], c + (size_t)i * n, row_bytes);

    free(a);
    free(b);
    free(c);
}

static const mma_callback_t _MMA_CALLBACK_MAP[NUM_MMAS] = {
    [MMA_NAIVE_IJK] = mat_mult_naive_ijk,
    [MMA_NAIVE_IKJ] = mat_mult_naive_ikj,
    [MMA_NAIVE_JIK] = mat_mult_naive_jik,
    [MMA_NAIVE_JKI] = mat_mult_naive_jki,
    [MMA_NAIVE_KIJ] = mat_mult_naive_kij,
    [MMA_NAIVE_KJI] = mat_mult_naive_kji,
    [MMA_OPENBLAS] = mat_mult_openblas,
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
