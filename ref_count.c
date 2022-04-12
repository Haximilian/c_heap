#include <stdlib.h>

#include "ref_count.h"

void del(ref_count_t* ref) {
    if (--ref->count == 0) {
       ref->free(ref);
    }
}

ref_count_t* copy(ref_count_t* ref) {
    ref->count++;

    return(ref);
}

ref_count_t* create_ref_count(void* ref) {
    ref_count_t* ret = malloc(sizeof(ref_count_t));
    ret->free = free;
    ret->count = 1;
    ret->ref = ref;

    return(ret);
}