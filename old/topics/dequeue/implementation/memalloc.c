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
    // buffer must be properly aligned
    uint8_t buffer[BLOCK_SIZE];
} block_t;

#ifdef  OPTIMIZED_IMPLEMENTATION

// global free list of available blocks - aligned for cache friendliness
static block_t *free_list __attribute__((aligned(64))) = NULL;

// track allocation size to optimize future allocations
static size_t last_allocation_size = 0;

// constants for optimization
#define INITIAL_ALLOCATION_SIZE 64                // start with a reasonable batch
#define MAX_ALLOCATION_SIZE 16384                 // cap growth to avoid excessive memory usage
#define ALLOCATION_GROWTH_FACTOR 2                // how much to grow by each time
#define PREFETCH_DISTANCE 2                       // how many blocks ahead to prefetch

// pre-allocate a batch of blocks and add to free list
static bool allocate_blocks(size_t num_blocks) {
    // allocate all blocks in a single contiguous chunk for cache locality
    // add extra space to ensure proper alignment
    const size_t alignment = 64;  // cache line size on most systems
    const size_t block_size = sizeof(block_t);
    const size_t aligned_block_size = ((block_size + alignment - 1) / alignment) * alignment;

    // allocate one large chunk
    uint8_t *memory = (uint8_t*)malloc(num_blocks * aligned_block_size + alignment);
    if (!memory) {
        return false;
    }

    // align the start address to cache line
    uintptr_t addr = (uintptr_t)memory;
    uintptr_t aligned_addr = (addr + alignment - 1) & ~(alignment - 1);
    uint8_t *aligned_memory = (uint8_t*)aligned_addr;

    // initialize blocks and add to free list
    block_t *prev_head = free_list;
    block_t *block;

    // work backwards to maintain cache-friendly allocation order
    for (size_t i = num_blocks; i > 0; i--) {
        block = (block_t*)(aligned_memory + (i-1) * aligned_block_size);
        block->next = prev_head;
        prev_head = block;

        // prefetch next blocks to improve cache performance
        if (i > PREFETCH_DISTANCE) {
            __builtin_prefetch(aligned_memory + (i-PREFETCH_DISTANCE-1) * aligned_block_size, 1, 3);
        }
    }

    free_list = block;  // update the head of our free list
    last_allocation_size = num_blocks;

    return true;
}

bool mem_init(size_t min_blocks) {
    if (free_list != NULL) {
        return false;  // already initialized
    }

    size_t initial_size = min_blocks > INITIAL_ALLOCATION_SIZE ? min_blocks : INITIAL_ALLOCATION_SIZE;
    return allocate_blocks(initial_size);
}

// hot path - make this as fast as possible
void *mem_alloc(void) {
    // fast path - just take from free list
    if (__builtin_expect(free_list != NULL, 1)) {  // optimize for the common case
        block_t *block = free_list;
        free_list = block->next;

        // prefetch next free block to minimize cache misses on next allocation
        if (free_list) {
            __builtin_prefetch(free_list, 0, 3);
        }

        // clear next pointer for safety
        block->next = NULL;

        // return only the buffer portion, not the whole block
        return block->buffer;
    }

    // slow path - need to allocate more blocks
    size_t new_size = last_allocation_size * ALLOCATION_GROWTH_FACTOR;
    if (new_size > MAX_ALLOCATION_SIZE) {
        new_size = MAX_ALLOCATION_SIZE;
    }

    if (!allocate_blocks(new_size)) {
        return NULL;  // failed to allocate more memory
    }

    // now we have blocks - retry allocation
    return mem_alloc();
}

// hot path - make this as fast as possible
void mem_free(void *ptr) {
    if (__builtin_expect(ptr == NULL, 0)) {  // optimize for the common case
        return;
    }

    // convert buffer pointer back to block pointer
    block_t *block = (block_t*)((char*)ptr - offsetof(block_t, buffer));

    // add to head of free list (LIFO for better cache locality)
    block->next = free_list;
    free_list = block;
}

// optional: add cleanup function to release all memory when done
void mem_cleanup(void) {
    // would require tracking allocated chunks - omitted for simplicity
    // in a full implementation, would free all allocated large chunks
    free_list = NULL;
    last_allocation_size = 0;
}

#endif


#ifdef LINKED_LIST_IMPLEMENTATION

// global free list of available blocks
block_t *free_list = NULL;
// current number of blocks in the system
size_t current_block_count = 0;

// allocate a new set of blocks and add them to the free list
bool allocate_more_blocks(const size_t num_blocks) {
    // allocate a batch of blocks using malloc
    for (size_t i = 0; i < num_blocks; i++) {
        // allocate a single block
        block_t *new_block = (block_t *) malloc(sizeof(block_t));
        if (!new_block) {
            fprintf(stderr, "malloc failed in allocate_more_blocks\n");
            return false; // allocation failed
        }

        // add the block to the front of the free list
        new_block->next = free_list;
        free_list = new_block;
    }

    // update the count of total blocks
    current_block_count += num_blocks;

    return true;
}

bool mem_init(const size_t min_blocks) {
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
            return NULL; // allocation failed
        }
    }

    // take the first block from the free list
    block_t *block = free_list;
    free_list = free_list->next;

    // clear next pointer to prevent use-after-free issues
    block->next = NULL;

    // return the buffer portion, not the whole block
    return block->buffer;
}

void mem_free(void *ptr) {
    if (!ptr) {
        return; // nothing to free
    }

    // convert buffer pointer back to block pointer
    block_t *block = (block_t *) ((char *) ptr - offsetof(block_t, buffer));

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

    // return the buffer portion, not the whole block
    return block->buffer;
}

void mem_free(void *ptr) {
    if (!ptr) {
        return; // nothing to free
    }

    // convert buffer pointer back to block pointer
    block_t *block = (block_t*)((char*)ptr - offsetof(block_t, buffer));

    // add the block to the front of the free list
    block->next = free_list;
    free_list = block;
}

#endif
