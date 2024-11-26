#ifndef __DATASTRUCTURE_H
#define __DATASTRUCTURE_H

#include <stdlib.h>

/* ---------------------------------------------- QUEUE ---------------------------------------------- */

typedef struct Node {
    int element;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* head;
    Node* tail;
    size_t size;
} Queue;

void QueueCreate(Queue* queue);

void QueuePush(Queue* queue, int element);
int QueuePop(Queue* queue);

int QueueHead(Queue* queue);
int QueueTail(Queue* queue);

size_t QueueSize(Queue* queue);

/* ---------------------------------------------- QUEUE ---------------------------------------------- */

#endif
