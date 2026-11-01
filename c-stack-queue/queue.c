#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

void queue_init(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

void queue_destroy(Queue *q) {
    int ignored;
    while (queue_dequeue(q, &ignored) == 0) {
        /* keep removing until empty */
    }
}

int queue_enqueue(Queue *q, int value) {
    QueueNode *node = malloc(sizeof *node);
    if (node == NULL) {
        return -1;
    }
    node->data = value;
    node->next = NULL;

    if (q->rear == NULL) {          /* empty queue: node is both front and rear */
        q->front = node;
    } else {
        q->rear->next = node;
    }
    q->rear = node;
    q->size++;
    return 0;
}

int queue_dequeue(Queue *q, int *out) {
    if (q->front == NULL) {
        return -1;
    }
    QueueNode *old = q->front;
    *out = old->data;
    q->front = old->next;
    if (q->front == NULL) {         /* queue became empty: rear must not dangle */
        q->rear = NULL;
    }
    free(old);
    q->size--;
    return 0;
}

int queue_peek(const Queue *q, int *out) {
    if (q->front == NULL) {
        return -1;
    }
    *out = q->front->data;
    return 0;
}

int queue_is_empty(const Queue *q) {
    return q->front == NULL;
}

size_t queue_size(const Queue *q) {
    return q->size;
}

void queue_print(const Queue *q) {
    printf("front -> ");
    for (const QueueNode *n = q->front; n != NULL; n = n->next) {
        printf("%d ", n->data);
    }
    printf("<- rear\n");
}
