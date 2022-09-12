//
// Created by Hello on 2022-05-09.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include "pubdef.h"


typedef struct queue {
    int size;
    int front;
    int rear;
    int length;
    elemtype* body;
} * queue;


queue Queue_New(int size);

queue Queue_FromArray(int size, elemtype arr[], int len);

bool Queue_IsEmpty(queue q);

void Queue_Clear(queue q);

bool Queue_IsFull(queue q);

static int Queue_Succ(queue q, int value);

status Queue_Enqueue(queue q, elemtype value);

elemtype Queue_Dequeue(queue q);

void Queue_Delete(queue q);

#define queue_fromarray(q, arr, len) Queue_FromArray(q, len, arr, len)


#endif //DATASTRUCTURE_QUEUE_H
