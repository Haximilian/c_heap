#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "heap.h"

#define ARR_LENGTH 128

int ord(void* elem) {
    return(*(int*)elem);
}

bool unittest(int* l, int* shuffle, size_t size) {
    heap_t* heap = create_heap(size, ord);

    for (int i = 0; i < size; i++) {
        heap_push(heap, &shuffle[i]);
    }

    printf("HEAP POP:\n");
    int* elem;
    for (int i = 0; i < size; i++){
        heap_pop(heap, &elem);
        printf("%d ", *elem);
        if (l[i] != *elem) {
            return false;
        }
    }
    printf("\n");

    return(true);
}

void arr_shuffle(int* arr, size_t size) {
    printf("SHUFFLE ARRAY:\n");
    for (size_t i = 0; i < size; i++) {
        int random = (rand() % (size - i)) + i; 
        int tmp = arr[random];
        arr[random] = arr[i];
        arr[i] = tmp;
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    srand(time(0));

    int arr[ARR_LENGTH];
    for (size_t i = 0; i < ARR_LENGTH; i++) {
        arr[i] = i;
    }

    int shuffle[ARR_LENGTH];
    memcpy(&shuffle, &arr, ARR_LENGTH * sizeof(int));
    arr_shuffle(&shuffle, ARR_LENGTH);

   if (unittest(&arr, &shuffle, ARR_LENGTH)) {
       printf("UNITTEST: PASS");
   } else {
       printf("UNITTEST: FAIL");
   }
   printf("\n");

   return(0);
}
