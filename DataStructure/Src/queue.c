//
// Created by Hello on 2022-05-09.
//

#include "queue.h"






bool Queue_IsEmpty(queue* q) {
    return q->length == 0;
}
bool Queue_IsFull(queue* q) {
    return q->length == q->size;
}

/**
 * clear a queue
 * @param q
 */
void Queue_Clear(queue* q) {
    q->length = 0;
    q->front = 0;
    q->rear = 1;
}



/**
 * if front or rear reaches the end, go back to beginning
 * @param pos
 * @param q
 * @return
 */
static int Queue_Succ(queue* q, int pos) {
    if (++pos == q->size)
        pos = 0;
    return pos;
}

status Queue_Enqueue(queue* q, elemtype value) {
    if (Queue_IsFull(q))
        return 1;  // queue full
    q->length++;
    q->rear = Queue_Succ(q, q->rear);
    q->body[q->rear] = value;
}


elemtype Queue_Dequeue(queue* q) {
    int elem;
    if (Queue_IsEmpty(q)) {
        /* queue empty */
        return 0;  // return to avoid warning
    }
    q->length--;
    elem = q->body[q->front];
    q->front = Queue_Succ(q->front, q);
    return elem;
}
