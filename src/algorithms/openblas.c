#include <algorithms/openblas.h>
#include <cblas.h>

void mat_mult_openblas(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
)
{
    const int n = mat1->size;

    openblas_set_num_threads(num_threads);

    // C = 1.0 * A * B + 0.0 * C  (mat_element_t is float -> sgemm)
    cblas_sgemm(
        CblasRowMajor, CblasNoTrans, CblasNoTrans,
        n, n, n,
        1.0f,
        mat1->data[0], n,
        mat2->data[0], n,
        0.0f,
        product->data[0], n
    );
}
