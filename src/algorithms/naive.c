#include <algorithms/naive.h>

void mat_mult_naive_ijk(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
)
{
    const mat_size_t size = mat1->size;

    for (mat_size_t i = 0; i < size; i++)
        for (mat_size_t j = 0; j < size; j++)
            for (mat_size_t k = 0; k < size; k++)
                (product->data)[i][j] += 
                    (mat1->data)[i][k] * (mat2->data)[k][j];
}

void mat_mult_naive_ikj(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
)
{
    const mat_size_t size = mat1->size;

    for (mat_size_t i = 0; i < size; i++)
        for (mat_size_t k = 0; k < size; k++)
            for (mat_size_t j = 0; j < size; j++)
                (product->data)[i][j] += 
                    (mat1->data)[i][k] * (mat2->data)[k][j];
}

void mat_mult_naive_jik(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
)
{
    const mat_size_t size = mat1->size;

    for (mat_size_t j = 0; j < size; j++)
        for (mat_size_t i = 0; i < size; i++)
            for (mat_size_t k = 0; k < size; k++)
                (product->data)[i][j] += 
                    (mat1->data)[i][k] * (mat2->data)[k][j];
}

void mat_mult_naive_jki(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
)
{
    const mat_size_t size = mat1->size;

    for (mat_size_t j = 0; j < size; j++)
        for (mat_size_t k = 0; k < size; k++)
            for (mat_size_t i = 0; i < size; i++)
                (product->data)[i][j] += 
                    (mat1->data)[i][k] * (mat2->data)[k][j];
}

void mat_mult_naive_kji(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
)
{
    const mat_size_t size = mat1->size;

    for (mat_size_t k = 0; k < size; k++)
        for (mat_size_t j = 0; j < size; j++)
            for (mat_size_t i = 0; i < size; i++)
                (product->data)[i][j] += 
                    (mat1->data)[i][k] * (mat2->data)[k][j];
}

void mat_mult_naive_kij(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
)
{
    const mat_size_t size = mat1->size;

    for (mat_size_t k = 0; k < size; k++)
        for (mat_size_t i = 0; i < size; i++)
            for (mat_size_t j = 0; j < size; j++)
                (product->data)[i][j] += 
                    (mat1->data)[i][k] * (mat2->data)[k][j];
}
