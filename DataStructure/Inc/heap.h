
#ifndef __HEAP_H__
#define __HEAP_H__

#include "pubdef.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define HEAP_MIN_ELEM 0
#define BINHEAP_BETTER_PRINT

typedef struct {
    int size;
    int length;
    elemtype* body;
} binheap;




typedef binheap* priority_queue;

uint32_t next_pow2(uint32_t v);

binheap* BinHeap_New(int size);

bool BinHeap_IsEmpty(binheap* heap);

bool BinHeap_IsFull(binheap* heap);

status BinHeap_Insert(binheap* heap, elemtype elem);

elemtype BinHeap_RemoveMin(binheap* heap);

void BinHeap_PrintArray(binheap* heap);

void BinHeap_PrintTree(binheap* heap);

void Array_PrintTree(const int *arr, size_t length);




typedef struct leftheap_node {
    elemtype elem;
    struct leftheap_node* left;
    struct leftheap_node* right;
    int Npl;
} leftheap_node, * leftheap;



leftheap LeftHeap_Merge(leftheap heap_A, leftheap heap_B);

leftheap LeftHeap_RemoveMin(leftheap heap);

leftheap LeftHeap_Insert(leftheap heap, elemtype elem);

#define leftheap_print(heap) LeftHeap_Print(heap, 0)

void LeftHeap_Print(leftheap tree, int depth);

#endif /* __HEAP_H__ */
