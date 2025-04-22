#include "memalloc.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#if defined(__SIZEOF_POINTER__)
#define PTR_SIZE __SIZEOF_POINTER__
#elif defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__)
    #define PTR_SIZE 8
#else
    #define PTR_SIZE 4
#endif

typedef struct block_ {
    struct block_ *next;
#if (BLOCK_SIZE - PTR_SIZE) > 0
    uint8_t buffer[BLOCK_SIZE - PTR_SIZE];
#endif
} block_t;

#ifdef LINKED_LIST_IMPLEMENTATION

// global free list of available blocks
block_t *free_list = NULL;
// current number of blocks in the system
size_t current_block_count = 0;

// allocate a new set of blocks and add them to the free list
bool allocate_more_blocks(size_t num_blocks) {
    // allocate a batch of blocks using malloc
    for (size_t i = 0; i < num_blocks; i++) {
        // allocate a single block
        block_t *new_block = (block_t *)malloc(sizeof(block_t));
        if (!new_block) {
            fprintf(stderr, "malloc failed in allocate_more_blocks\n");
            return false;  // allocation failed
        }

        // add the block to the front of the free list
        new_block->next = free_list;
        free_list = new_block;
    }

    // update the count of total blocks
    current_block_count += num_blocks;

    return true;
}

bool mem_init(size_t min_blocks) {
    // ensure we have no existing allocation
    if (free_list != NULL) {
        return false;
    }

    // allocate the initial set of blocks
    return allocate_more_blocks(min_blocks);
}

void *mem_alloc() {
    // if no free blocks are available, double the capacity
    if (!free_list) {
        size_t new_blocks = current_block_count > 0 ? current_block_count * 2 : 1;
        if (!allocate_more_blocks(new_blocks)) {
            return NULL;  // allocation failed
        }
    }

    // take the first block from the free list
    block_t *block = free_list;
    free_list = free_list->next;

    // clear next pointer to prevent use-after-free issues
    block->next = NULL;

    // return the block itself as the allocated memory
    return (void *)block;
}

void mem_free(void *ptr) {
    if (!ptr) {
        return;  // nothing to free
    }

    // cast back to block_t
    block_t *block = (block_t *)ptr;

    // add the block to the front of the free list
    block->next = free_list;
    free_list = block;
}

#endif

#ifdef SYSTEM_CALL_IMPLEMENTATION

// global free list of available blocks
block_t *free_list = NULL;
// current number of blocks in the system
size_t current_block_count = 0;

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <errno.h>
#endif

// allocate a new set of blocks and add them to the free list
bool allocate_more_blocks(size_t num_blocks) {
    size_t size = num_blocks * sizeof(block_t);

#ifdef _WIN32
    void *mem = VirtualAlloc(
        NULL,                // let the system decide address
        size,                // total size
        MEM_COMMIT | MEM_RESERVE, // commit and reserve pages
        PAGE_READWRITE       // read/write access
    );
    if (mem == NULL) {
        fprintf(stderr, "VirtualAlloc failed: %lu\n", GetLastError());
        return false;
    }
#else
    void *mem = mmap(
        NULL, // let the kernel choose the address
        size, // number of bytes to allocate
        PROT_READ | PROT_WRITE, // read/write access
        MAP_PRIVATE | MAP_ANONYMOUS, // not backed by any file
        -1, // required for MAP_ANONYMOUS
        0 // offset
    );
    if (mem == MAP_FAILED) {
        perror("mmap failed");
        return false;
    }
#endif

    // initialize each block and add to the free list
    block_t *curr = (block_t *) mem;
    for (size_t i = 0; i < num_blocks - 1; i++) {
        curr->next = (block_t *) ((uint8_t *) curr + sizeof(block_t));
        curr = curr->next;
    }

    // connect the last block to the existing free list
    curr->next = free_list;
    // set the free list to point to the beginning of the new blocks
    free_list = (block_t *) mem;

    // update the count of total blocks
    current_block_count += num_blocks;

    return true;
}

bool mem_init(size_t min_blocks) {
    // ensure we have no existing allocation
    if (free_list != NULL) {
        return false;
    }

    // allocate the initial set of blocks
    return allocate_more_blocks(min_blocks);
}

void *mem_alloc() {
    // if no free blocks are available, double the capacity
    if (!free_list) {
        size_t new_blocks = current_block_count > 0 ? current_block_count : 1;
        if (!allocate_more_blocks(new_blocks)) {
            return NULL; // allocation failed
        }
    }

    // take the first block from the free list
    block_t *block = free_list;
    free_list = free_list->next;

    // clear next pointer to prevent use-after-free issues
    block->next = NULL;

    // return the block itself as the allocated memory
    return (void *) block;
}

void mem_free(void *ptr) {
    if (!ptr) {
        return; // nothing to free
    }

    // cast back to block_t
    block_t *block = (block_t *) ptr;

    // add the block to the front of the free list
    block->next = free_list;
    free_list = block;
}

#endif

