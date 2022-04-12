#include <stdbool.h>
#include <stddef.h>

#include "ref_count.h"

typedef struct heap_node heap_node_t;
struct heap_node {
    ref_count_t* indirect;
    void* elem;
};

typedef struct heap heap_t;
struct heap {
    size_t size;
    size_t cap;
    int (*ord)(void*);
    heap_node_t arr[0];
};


// todo:
// add const to void*
// this would only make the ptr const rather than the values of the object
heap_t* create_heap(size_t cap, int (*ord)(void*));

// returns null if not succesful
// double pointer is necessary indirection since nodes change position in backing arr
ref_count_t* heap_push(heap_t* heap, void* ptr);

bool heap_pop(heap_t* heap, void** r_val);