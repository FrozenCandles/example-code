//
// Created by Hello on 2022-08-06.
//

#include "linkedlist.h"


/**
 * print elements from L according to P
 * @param L
 * @param P
 */
void LinkedList_PrintLots(linkedlist L, linkedlist P) {
    P->elem = 0;
    while (P->next) {
        for (int i = 0; i < P->next->elem - P->elem; i++)
            if (L->next)
                L = L->next;
        printf("%d, ", L->elem);
        P = P->next;
    }
}

/**
 * exchange element between former and latter by adjusting pointers
 * position starts with 0
 * @param list
 * @param pos
 */
status LinkedList_Swap(linkedlist list, int pos) {
    for (int i = 0; i < pos; i++) {
        if (list->next)
            list = list->next;
        else
            return 1;
    }
    linkedlist_node* prev = list;
    linkedlist_node* this = prev->next;
    linkedlist_node* next = this->next;
    linkedlist_node* nnxt = next->next;

    prev->next = next;
    this->next = nnxt;
    next->next = this;
    return 0;
}

/**
 *
 * @param a need to be orderly
 * @param b need to be orderly
 * @return
 */
linkedlist LinkedList_Intersection(linkedlist a, linkedlist b) {
    linkedlist result = malloc(sizeof(linkedlist_node));
    if (!result)
        return NULL;  // fail to allocate memory
    result->next = NULL;

    a = a->next;
    b = b->next;
    while (a != NULL && b != NULL) {
        if (a->elem < b->elem)
            a = a->next;
        else if (a->elem > b->elem)
            b = b->next;
        else {
            LinkedList_InsertAfter(result, a->elem);
            a = a->next;
            b = b->next;
        }
    }
    return result;
}

linkedlist LinkedList_Union(linkedlist a, linkedlist b) {
    linkedlist_node* header = malloc(sizeof(linkedlist_node));
    if (!header)
        return NULL;

    header->next = NULL;
    a = a->next;
    b = b->next;

    while (a != NULL && b != NULL) {
        if (a->elem < b->elem) {
            LinkedList_InsertAfter(header, a->elem);
            a = a->next;
        }
        else if (a->elem > b->elem) {
            LinkedList_InsertAfter(header, a->elem);
            b = b->next;
        }
        else {
            LinkedList_InsertAfter(header, a->elem);
            a = a->next;
            b = b->next;
        }
    }
    return header;
}


void test_linkedlist_operations(void) {

    linkedlist_node* list = LinkedList_FromArray((int[]){ 0, 1, 2, 4, 6 }, 5);
    LinkedList_Println(list);

    LinkedList_InsertAfter(LinkedList_GetNode(list, 2), 3);
    LinkedList_Println(list);

    LinkedList_Remove(list, 6);
    LinkedList_Println(list);

    LinkedList_Clear(list);
    LinkedList_Println(list);
}

void test_linkedlist_operations_more(void) {

    printf("Linkedlist L: \n    ");
    linkedlist list_L = LinkedList_FromArray((int [7]){ 1, 2, 4, 6, 7, 9, 10 }, 7);
    LinkedList_Println(list_L);

    printf("Linkedlist P: \n    ");
    linkedlist list_P = LinkedList_FromArray((int [4]){ 1, 3, 4, 6 }, 4);
    LinkedList_Println(list_P);

    /* Elements from linkedlist L with position in linkedlist P */
    printf("Print lots: \n    ");
    LinkedList_PrintLots(list_L, list_P);
    putchar('\n');

    puts("Exchange 2nd and 3rd element from linkedlist P:");
    printf("  Before exchange: ");
    LinkedList_Println(list_P);
    LinkedList_Swap(list_P, 1);
    printf("  After exchange : ");
    LinkedList_Println(list_P);


    linkedlist list_A = LinkedList_FromArray((int [7]){ 0, 1, 3, 4, 6, 7, 9 }, 7);
    linkedlist list_B = LinkedList_FromArray((int [7]){ 1, 2, 3, 6, 7, 8, 9 }, 7);
    puts("Linkedlist A and B:");
    printf("    A: ");
    LinkedList_Println(list_A);
    printf("    B: ");
    LinkedList_Println(list_B);

    printf("Intersection   : ");
    LinkedList_Println(LinkedList_Intersection(list_A, list_B));

    linkedlist list_U = LinkedList_Union(list_A, list_B);
    printf("Union          : ");
    LinkedList_Println(list_U);

    printf("Union reversed : ");
    LinkedList_Println(LinkedList_Reverse(list_U));
}