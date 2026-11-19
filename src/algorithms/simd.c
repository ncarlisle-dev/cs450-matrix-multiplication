#include <algorithms/simd.h>

#include <immintrin.h>

/*
 * AVX2 registers are 256 bits wide, so one vector holds 4 doubles or 8 floats.
 * The helpers below pick the right intrinsic based on mat_element_t; the
 * sizeof() checks are compile-time constants, so the unused branch is removed.
 */
#define SIMD_WIDTH ((unsigned int)(32 / sizeof(mat_element_t)))

/* c[0..W) += a * b[0..W) using one fused multiply-add */
static inline void _simd_fma_row(
    mat_element_t* const c,
    const mat_element_t* const b,
    const mat_element_t a
)
{
    if (sizeof(mat_element_t) == sizeof(double))
    {
        const __m256d a_vec = _mm256_set1_pd((double)a);           /* broadcast A[i][k] */
        const __m256d b_vec = _mm256_loadu_pd((const double*)b);   /* B[k][j..j+3] */
        __m256d       c_vec = _mm256_loadu_pd((double*)c);         /* C[i][j..j+3] */
        c_vec = _mm256_fmadd_pd(a_vec, b_vec, c_vec);
        _mm256_storeu_pd((double*)c, c_vec);
    }
    else
    {
        const __m256 a_vec = _mm256_set1_ps((float)a);             /* broadcast A[i][k] */
        const __m256 b_vec = _mm256_loadu_ps((const float*)b);     /* B[k][j..j+7] */
        __m256       c_vec = _mm256_loadu_ps((float*)c);           /* C[i][j..j+7] */
        c_vec = _mm256_fmadd_ps(a_vec, b_vec, c_vec);
        _mm256_storeu_ps((float*)c, c_vec);
    }
}

static inline unsigned int _min(const unsigned int a, const unsigned int b)
{
    return a < b ? a : b;
}

void mat_mult_simd(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
)
{
    /* use unsigned int indices so j + SIMD_WIDTH can't overflow mat_size_t */
    const unsigned int size = mat1->size;
    const unsigned int tile = SIMD_TILE_SIZE;

    mat_element_t* const* const A = mat1->data;
    mat_element_t* const* const B = mat2->data;
    mat_element_t* const* const C = product->data;

    /*
     * Thread-level parallelism on top of the SIMD kernel. Each (ii, jj) pair
     * owns a distinct tile of C, so threads never write the same element and
     * no synchronization is needed. The kk loop stays inside each task because
     * different kk values accumulate into the same C tile. collapse(2) turns
     * the (ii, jj) grid into (size/tile)^2 independent tasks for load balance.
     */
    #pragma omp parallel for collapse(2) schedule(static) num_threads(num_threads)
    for (unsigned int ii = 0; ii < size; ii += tile)
    {
        for (unsigned int jj = 0; jj < size; jj += tile)
        {
            const unsigned int i_end = _min(ii + tile, size);
            const unsigned int j_end = _min(jj + tile, size);

            for (unsigned int kk = 0; kk < size; kk += tile)
            {
                const unsigned int k_end = _min(kk + tile, size);

                for (unsigned int i = ii; i < i_end; i++)
                {
                    mat_element_t* const c_row = C[i];

                    for (unsigned int k = kk; k < k_end; k++)
                    {
                        const mat_element_t        a     = A[i][k];
                        const mat_element_t* const b_row = B[k];

                        /* vectorized body: SIMD_WIDTH columns per FMA */
                        unsigned int j = jj;
                        for (; j + SIMD_WIDTH <= j_end; j += SIMD_WIDTH)
                            _simd_fma_row(&c_row[j], &b_row[j], a);

                        /* scalar tail for widths not divisible by SIMD_WIDTH */
                        for (; j < j_end; j++)
                            c_row[j] += a * b_row[j];
                    }
                }
            }
        }
    }
}
