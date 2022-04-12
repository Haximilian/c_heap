#include <stdlib.h>

// todo:
// the type should be more generic
// at the moment, our object is of type void*
// replace this with 
// char obj[0]

// doc:
// the function pointer 'free'
// can be set to either stdlib free,
// a slot allocator or any other 
// memory allocator

// doc:
// ref_count is necessary when
// free order is non-deterministic and
// ownership of an obj is shared

typedef struct ref_count ref_count_t;
struct ref_count {
    void (*free)(void*);
    size_t count;
    void* ref;
};

ref_count_t* create_ref_count(void* ref);

void del(ref_count_t* ref);

ref_count_t* copy(ref_count_t* ref);