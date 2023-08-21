#ifndef FENNEC_DYN_ARRAY
#define FENNEC_DYN_ARRAY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    // the length or number of elements currently within the data structure
    size_t length;

    // the maximum capacity that the data structure can hold
    size_t cap;

    // the size of each element in the array
    size_t elem_size;

    // the array of pointers to data that can be allocated on the top of the
    // vector
    void *data;
} FennecDynArray;

/*
 * @description
 * Creates a new generic dynamic array. The capacity and the length are
 * initialized to zero
 *
 * @argument
 * The size of each element that is pushed to the array
 *
 * @returns
 * Returns a pointer to an allocated dynamic array. All data is by default
 * allocated on the heap, including the dynamic array structure itself.
 * Therefore, once you are done with the array it is important to free the
 * array
 */
FennecDynArray *fennec_dynarray_new(size_t);

/*
 * @description
 * Pushes an element to the end of the array. If the length of the array plus
 * the new element is greater than the capacity of the array, the capacity
 * is doubled and the data is reallocated.
 *
 * @argument 2: A pointer to the data that is to be copied into the array
 */
void fennec_dynarray_push(FennecDynArray*, void*);

/*
 * @description
 * Deletes the top value from the array
 */
void fennec_dynarray_pop(FennecDynArray*);

/*
 * @description
 * Frees all memory allocated to the dynamic array, also frees the dynamic
 * array object itself
 */
void fennec_dynarray_free(FennecDynArray*);

/*
 * @description
 * Returns a pointer to the top value on the array
 */
void *fennec_dynarray_top(FennecDynArray*);

/*
 * @description
 * Performs arithmetic on the internal array in order to get pointer to an
 * element in the array.
 *
 * @argument
 * The index of the element
 *
 * @returns
 * A pointer to the data inside the internal array
 */
void *fennec_dynarray_get(FennecDynArray*, size_t);

#endif
