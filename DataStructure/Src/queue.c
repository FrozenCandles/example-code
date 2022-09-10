//
// Created by Hello on 2022-05-09.
//

#include "queue.h"






bool Queue_IsEmpty(queue q) {
    return q->length == 0;
}


bool Queue_IsFull(queue q) {
    return q->length == q->size;
}

/**
 * clear a queue
 * @param q
 */
void Queue_Clear(queue q) {
    q->length = 0;
    q->front = 1;
    q->rear = 0;
}


queue Queue_New(int size) {
    queue q = malloc(sizeof(struct queue));
    Queue_Clear(q);
    q->body = malloc(size * sizeof(elemtype));
    q->size = size;
    return q;
}


queue Queue_FromArray(int size, elemtype arr[], int len) {
    queue q = Queue_New(size);
    for (int i = 0; i < len; i++)
        Queue_Enqueue(q, arr[i]);
    return q;
}

/**
 * if front or rear reaches the end, go back to beginning
 * @param pos
 * @param q
 * @return
 */
static int Queue_Succ(queue q, int pos) {
    if (++pos == q->size)
        pos = 0;
    return pos;
}

status Queue_Enqueue(queue q, elemtype value) {
    if (Queue_IsFull(q))
        return 1;  // queue full
    q->length++;
    q->rear = Queue_Succ(q, q->rear);
    q->body[q->rear] = value;
    return 0;
}


elemtype Queue_Dequeue(queue q) {
    int elem;
    if (Queue_IsEmpty(q)) {
        /* queue empty */
        return 0;  // return to avoid warning
    }
    q->length--;
    elem = q->body[q->front];
    q->front = Queue_Succ(q, q->front);
    return elem;
}




