#include <stdbool.h>
#include <stddef.h>

typedef struct heap heap_t;
struct heap {
    size_t size;
    size_t cap;
    int (*ord)(void*);
    void* arr[0];
};

heap_t* create_heap(size_t cap, int (*ord)(void*));

bool heap_push(heap_t* heap, void* ptr);

bool heap_pop(heap_t* heap, void** r_val);