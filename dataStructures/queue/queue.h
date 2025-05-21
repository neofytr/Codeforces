#include <stdlib.h>

#define TYPE int

typedef struct node_ node_t;
typedef bool (*compare_t)(TYPE *data_one, TYPE *data_two);

struct node_
{
    struct node_ *next;
    TYPE data;
};


