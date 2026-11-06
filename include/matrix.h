#pragma once

typedef unsigned short mat_size_t;
typedef double mat_member_t;

typedef struct
{
    mat_size_t size;
    mat_member_t** data;
} mat_t;

mat_t* mat_create(const mat_size_t size);
void mat_delete(mat_t** const mat);
void mat_print(const mat_t* const mat);
void mat_randomize(const mat_t* const mat);
