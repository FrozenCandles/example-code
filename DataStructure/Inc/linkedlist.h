//
// Created by Hello on 2022-05-05.
//

#ifndef DATASTRUCTURE_LINKEDLIST_H
#define DATASTRUCTURE_LINKEDLIST_H

#include "pubdef.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct linkedlist_node {
    elemtype elem;
    struct linkedlist_node* next;
} linkedlist_node, * linkedlist;


typedef struct dulinkedlist_node {
    elemtype elem;
    struct dulinkedlist_node* prev;
    struct dulinkedlist_node* next;
} dulinkedlist_node, * dulinkedlist;

typedef linkedlist_node clinkedlist_node, * clinkedlist;

/* create and delete */

linkedlist LinkedList_New(void);

void LinkedList_Clear(linkedlist l);

void LinkedList_Delete(linkedlist l);

linkedlist LinkedList_FromArray(const elemtype values[], int length);

bool LinkedList_IsEmpty(linkedlist list);

bool LinkedList_IsLast(linkedlist list);

/* node operation */

linkedlist_node* LinkedList_GetNode(linkedlist_node* node, elemtype value);

linkedlist_node* LinkedList_GetPrevNode(linkedlist list, elemtype value);

status LinkedList_Remove(linkedlist list, elemtype value);

status LinkedList_InsertAfter(linkedlist_node* prev, elemtype value);

void LinkedList_Print(linkedlist_node* header);

void LinkedList_Println(linkedlist_node* header);

linkedlist LinkedList_Reverse(linkedlist list);







#endif //DATASTRUCTURE_LINKEDLIST_H
