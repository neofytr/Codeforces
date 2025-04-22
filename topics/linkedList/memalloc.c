#include "memalloc.h"

#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>

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

block_t *free_list = NULL;
