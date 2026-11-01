#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

/*
 * FIFO queue of ints, built from a singly linked list with front and rear
 * pointers, so both enqueue and dequeue are O(1).
 *
 * Same conventions as Stack: 0 = success, -1 = failure, values returned
 * through an output pointer.
 */
typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
    size_t size;
} Queue;

void   queue_init(Queue *q);
void   queue_destroy(Queue *q);
int    queue_enqueue(Queue *q, int value);
int    queue_dequeue(Queue *q, int *out);
int    queue_peek(const Queue *q, int *out);
int    queue_is_empty(const Queue *q);
size_t queue_size(const Queue *q);
void   queue_print(const Queue *q);

#endif
