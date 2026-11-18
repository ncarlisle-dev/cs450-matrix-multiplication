#include <matrix.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

mat_t* mat_create(const mat_size_t size)
{
    assert(size > 0);

    mat_t* mat = (mat_t*)calloc(1, sizeof(mat_t));
    mat->data = (mat_element_t**)calloc(size, sizeof(mat_element_t*));

    for (mat_size_t i = 0; i < size; i++)
        mat->data[i] = (mat_element_t*)calloc(size, sizeof(mat_element_t));

    mat->size = size;
    
    return mat;
}

void mat_delete(mat_t** const mat)
{
    for (mat_size_t i = 0; i < (*mat)->size; i++)
        free((*mat)->data[i]);

    free((*mat)->data);
    free(*mat);
    *mat = NULL;
}

void mat_print(const mat_t* const mat)
{
    for (mat_size_t row = 0; row < mat->size; row++)
    {
        for (mat_size_t col = 0; col < mat->size; col++)
        {
            printf("%lf ", (mat->data)[row][col]);
        }

        printf("\n");
    }
}

static mat_element_t _generate_random_element(
    const mat_element_t min,
    const mat_element_t max
) {
    // generate a random float/double
    mat_element_t scale = (mat_element_t)rand() / RAND_MAX;
    return min + scale * (max - min);
}

void mat_randomize(const mat_t* const mat)
{
    for (mat_size_t row = 0; row < mat->size; row++)
        for (mat_size_t col = 0; col < mat->size; col++)
            mat->data[row][col] = _generate_random_element(-100, 100);
}
