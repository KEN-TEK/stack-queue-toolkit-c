#include "stack.h"

#include <stdlib.h>

#define INITIAL_CAPACITY 8

int stack_init(Stack *s) {
    s->size = 0;
    s->capacity = 0;
    s->items = malloc(INITIAL_CAPACITY * sizeof *s->items);
    if (s->items == NULL) {
        return -1;
    }
    s->capacity = INITIAL_CAPACITY;
    return 0;
}

void stack_destroy(Stack *s) {
    free(s->items);
    s->items = NULL;
    s->size = 0;
    s->capacity = 0;
}

int stack_push(Stack *s, int value) {
    if (s->size == s->capacity) {
        size_t new_capacity = s->capacity ? s->capacity * 2 : INITIAL_CAPACITY;
        int *bigger = realloc(s->items, new_capacity * sizeof *bigger);
        if (bigger == NULL) {
            return -1;              /* old buffer is still valid and still owned by s */
        }
        s->items = bigger;
        s->capacity = new_capacity;
    }
    s->items[s->size++] = value;
    return 0;
}

int stack_pop(Stack *s, int *out) {
    if (s->size == 0) {
        return -1;
    }
    *out = s->items[--s->size];
    return 0;
}

int stack_peek(const Stack *s, int *out) {
    if (s->size == 0) {
        return -1;
    }
    *out = s->items[s->size - 1];
    return 0;
}

int stack_is_empty(const Stack *s) {
    return s->size == 0;
}

size_t stack_size(const Stack *s) {
    return s->size;
}
