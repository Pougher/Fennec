#include "dynarray.h"

FennecDynArray *fennec_dynarray_new(size_t elem_size) {
    FennecDynArray *new_arr = malloc(sizeof(FennecDynArray));

    new_arr->length = 0;
    new_arr->cap = 1;
    new_arr->elem_size = elem_size;
    new_arr->data = NULL;

    return new_arr;
}

void fennec_dynarray_push(FennecDynArray *arr, void *data) {
    if (arr->length + 1 == arr->cap) {
        arr->cap *= 2;
        arr->data = realloc(arr->data, arr->cap * arr->elem_size);
    }
    memcpy(
        (char*)arr->data + (arr->length * arr->elem_size),
        data,
        arr->elem_size);
    arr->length++;
}

void fennec_dynarray_pop(FennecDynArray *arr) {
    arr->length--;
}

void fennec_dynarray_free(FennecDynArray *arr) {
    free(arr->data);
    free(arr);
}

void *fennec_dynarray_top(FennecDynArray *arr) {
    void* index = (char*)arr->data + ((arr->length - 1) * arr->elem_size);
    return index;
}

void *fennec_dynarray_get(FennecDynArray *arr, size_t index) {
    void* idx = (char*)arr->data + (index * arr->elem_size);
    return idx;
}
