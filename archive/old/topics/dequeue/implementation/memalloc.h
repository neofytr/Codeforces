#ifndef MEMALLOC_H
#define MEMALLOC_H

#define BLOCK_SIZE (24)
#define LINKED_LIST_IMPLEMENTATION

#include <stdbool.h>
#include <stddef.h>

bool mem_init(size_t min_blocks);

void *mem_alloc(); // allocates chunks of BLOCK_SIZE bytes

void mem_free(void *ptr);
#endif //MEMALLOC_H
