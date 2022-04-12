#include "heap.h"

#include <stdlib.h>

heap_t* create_heap(size_t cap, int (*ord)(void*)) {
    heap_t* heap = malloc(sizeof(heap_t) + cap * sizeof(heap_node_t));
    heap->size = 0;
    heap->cap = cap;
    heap->ord = ord;

    return(heap);
}

void _update_ref(heap_node_t* t) {
    t->indirect->ref = t;
}

void _swap(heap_node_t* l, heap_node_t* r) {
    heap_node_t t = *l;
    *l = *r;
    *r = t;

    _update_ref(l);
    _update_ref(r);
}

ref_count_t* heap_push(heap_t* heap, void* ptr) {
    if (heap->size >= heap->cap) {
        return(NULL);
    }

    size_t curr = heap->size++;
    size_t parent = (curr - 1) / 2;

    ref_count_t* ret = create_ref_count(&heap->arr[curr]);

    heap->arr[curr].indirect = copy(ret);
    heap->arr[curr].elem = ptr;

    while (curr != 0 && heap->ord(heap->arr[parent].elem) > heap->ord(heap->arr[curr].elem)) {
        _swap(&heap->arr[curr], &heap->arr[parent]);

        curr = parent;
        parent = (curr - 1) / 2;
    }

    return(ret);
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
            if (heap->ord(heap->arr[l].elem) < heap->ord(heap->arr[r].elem)) {
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

        if (heap->ord(heap->arr[curr].elem) > heap->ord(heap->arr[small].elem)) {
            _swap(&heap->arr[small], &heap->arr[curr]);

            curr = small;
        } else {
            break;
        }
    }
}

bool heap_pop(heap_t* heap, void** ret) {
    if (heap->size == 0) {
        return(false);
    }

    *ret = heap->arr[0].elem;
    _swap(&heap->arr[0], &heap->arr[--heap->size]);
    del(heap->arr[heap->size].indirect);

    _bubble_down(heap, 0);

    return(true);
}
