



#include "heap.h"


void test_binheap_operations(void) {

    srand(4);

    binheap* heap = BinHeap_New(128);
    for (int i = 1; i < 20; ++i)
        BinHeap_Insert(heap, rand() % 100);

    BinHeap_PrintTree(heap);

    BinHeap_Insert(heap, 6);

    BinHeap_PrintTree(heap);

    printf("Remove minimum: %d\n", BinHeap_RemoveMin(heap));

    BinHeap_PrintTree(heap);

    printf("Remove minimum: %d\n", BinHeap_RemoveMin(heap));

    BinHeap_PrintTree(heap);

    printf("Remove minimum: %d\n", BinHeap_RemoveMin(heap));

    BinHeap_PrintTree(heap);
//    BinHeap_Insert(heap, )

}


void test_leftheap_merge(void) {

    srand(10);

    printf("Leftist heap A: \n");
    leftheap heap_A = malloc(sizeof(leftheap_node));
    heap_A->elem = 3;
    heap_A->left = heap_A->right = NULL;
    for (int i = 0; i < 20; i++)
        LeftHeap_Insert(heap_A, rand() % 50 + 5);

    leftheap_print(heap_A);
    putchar('\n');

    printf("Leftist heap B: \n");
    leftheap heap_B = malloc(sizeof(leftheap_node));
    heap_B->elem = 4;
    heap_B->left = heap_B->right = NULL;
    for (int i = 0; i < 20; i++)
        LeftHeap_Insert(heap_B, rand() % 50 + 5);

    printf("Merge heap A and B: \n");
    leftheap_print(LeftHeap_Merge(heap_A, heap_B));
}

