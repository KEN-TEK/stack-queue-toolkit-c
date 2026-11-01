#ifndef STACK_H
#define STACK_H

#include <stddef.h>

/*
 * Dynamic array stack of ints. It starts small and doubles when full,
 * so there is no fixed maximum size.
 *
 * Functions that can fail return 0 on success and -1 on failure
 * (allocation failure, or popping/peeking an empty stack).
 * Values are returned through an output pointer, so every int is a valid
 * stack value (no "-1 means error" ambiguity).
 */
typedef struct {
    int *items;
    size_t size;
    size_t capacity;
} Stack;

int    stack_init(Stack *s);
void   stack_destroy(Stack *s);
int    stack_push(Stack *s, int value);
int    stack_pop(Stack *s, int *out);
int    stack_peek(const Stack *s, int *out);
int    stack_is_empty(const Stack *s);
size_t stack_size(const Stack *s);

#endif
