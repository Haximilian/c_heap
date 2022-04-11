#include "heap.h"

#include <stdlib.h>

heap_t* create_heap(size_t cap, int (*ord)(void*)) {
    heap_t* heap = malloc(sizeof(heap_t) + cap * sizeof(void*));
    heap->size = 0;
    heap->cap = cap;
    heap->ord = ord;

    return(heap);
}

bool heap_push(heap_t* heap, void* ptr) {
    if (heap->size >= heap->cap) {
        return(false);
    }

    size_t curr = heap->size++;
    size_t parent = (curr - 1) / 2;

    heap->arr[curr] = ptr;

    while (curr != 0 && heap->ord(heap->arr[parent]) > heap->ord(heap->arr[curr])) {
        heap->arr[curr] = heap->arr[parent];
        heap->arr[parent] = ptr;

        curr = parent;
        parent = (curr - 1) / 2;
    }

    return(true);
}

void _bubble_down(heap_t* heap, int curr) {
    size_t l;
    size_t r;
    size_t small;
    void* t;

    for (;;) {
        l = curr * 2 + 1;
        r = curr * 2 + 2;

        if (l < heap->size && r < heap->size) {
            if (heap->ord(heap->arr[l]) < heap->ord(heap->arr[r])) {
                small = l;
            } else {
                small = r;
            }
        }

        if (l < heap->size && r >= heap->size) {
            small = l;
        }

        if (l >= heap->size && r >= heap->size) {
            break;
        }

        if (heap->ord(heap->arr[curr]) > heap->ord(heap->arr[small])) {
            t = heap->arr[small];
            heap->arr[small] = heap->arr[curr];
            heap->arr[curr] = t;

            curr = small;
        } else {
            break;
        }
    }
}

bool heap_pop(heap_t* heap, void** r_val) {
    if (heap->size == 0) {
        return(false);
    }

    *r_val = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];

    _bubble_down(heap, 0);

    return(true);
}
