#pragma once
#include <matrix.h>

/**
 * Edge length (in elements) of the square tiles used by the SIMD kernel.
 * Can be overridden at compile time, e.g. -DSIMD_TILE_SIZE=128.
 */
#ifndef SIMD_TILE_SIZE
#define SIMD_TILE_SIZE 64
#endif

/**
 * Tiled matrix multiplication whose innermost loop uses AVX2 FMA intrinsics.
 *
 * For each (i, k) pair inside a tile, the scalar mat1[i][k] is broadcast into
 * a vector register, multiplied against a vector of consecutive entries of
 * row k of mat2, and accumulated into the matching entries of row i of the
 * product (4 doubles or 8 floats per instruction, depending on mat_element_t).
 *
 * Requires a CPU with AVX2 + FMA and compilation with -mavx2 -mfma.
 */
void mat_mult_simd(
    const mat_t* const mat1,
    const mat_t* const mat2,
    const mat_t* const product,
    const unsigned short num_threads
);
