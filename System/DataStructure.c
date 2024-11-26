#include "DataStructure.h"

/* ---------------------------------------------- QUEUE ---------------------------------------------- */

void QueueCreate(Queue* queue)
{
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

void QueuePush(Queue* queue, int element)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->element = element;
    newNode->next = NULL;

    if (queue->tail == NULL)
    {
        queue->head = newNode;
        queue->tail = newNode;
    }

    else
    {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    queue->size++;
}

int QueuePop(Queue* queue)
{
    int element = queue->head->element;
    Node* temp = queue->head;
    queue->head = queue->head->next;

    free(temp);

    queue->size--;

    if (queue->size == 0)
    {
        queue->tail = NULL;
    }

    return element;
}

int QueueHead(Queue* queue)
{
    return queue->head->element;
}

int QueueTail(Queue* queue) 
{
    return queue->tail->element;
}

size_t QueueSize(Queue* queue)
{
    return queue->size;
}

/* ---------------------------------------------- QUEUE ---------------------------------------------- */
