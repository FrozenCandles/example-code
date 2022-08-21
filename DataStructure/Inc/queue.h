//
// Created by Hello on 2022-05-09.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H

#include <stdio.h>

#include "pubdef.h"


typedef struct {
    int size;
    int front;
    int rear;
    int length;
    elemtype* body;
} queue;

bool Queue_IsEmpty(queue* q);

void Queue_Clear(queue* q);

bool Queue_IsFull(queue* q);

static int Queue_Succ(queue* q, int value);

status Queue_Enqueue(queue* q, elemtype value);

elemtype Queue_Dequeue(queue* q);




#endif //DATASTRUCTURE_QUEUE_H
