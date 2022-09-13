//
// Created by Hello on 2022-05-08.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H


#include <stdio.h>
#include <stdlib.h>

#include "pubdef.h"
#include "linkedlist.h"

typedef struct {
    int size;
    int topptr;
    elemtype* body;
} stack;

#define STACK_NULLTOP (0)

#define STACK_MINLEN (2)

typedef linkedlist linkedstack;



stack* Stack_New(int capacity);

bool Stack_IsFull(stack* s);

status Stack_Push(elemtype value, stack* s);

bool Stack_IsEmpty(stack* s);

status Stack_Pop(stack* s);

void Stack_Clear(stack* s);

void Stack_Delete(stack* s);

elemtype Stack_Top(stack* s);

elemtype Stack_PopTop(stack* s);

/* Linked Stack */

#define LinkedStack_New LinkedList_New

#define LinkedStack_Delete LinkedList_Delete

bool LinkedStack_IsEmpty(linkedstack s);

status LinkedStack_Push(linkedstack s, elemtype value);

status LinkedStack_Pop(linkedstack s);

elemtype LinkedStack_Top(linkedstack s);

status LinkedStack_Clear(linkedstack s);


#endif //DATASTRUCTURE_STACK_H
