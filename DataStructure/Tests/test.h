//
// Created by Hello on 2022-08-06.
//

#ifndef DATASTRUCTURE_TEST_H
#define DATASTRUCTURE_TEST_H

#include "../datastructure.h"

/**
 * @addtogroup LinkedList
 * @{
 */


void LinkedList_PrintLots(linkedlist L, linkedlist P);

status LinkedList_Swap(linkedlist list, int pos);

linkedlist LinkedList_Intersection(linkedlist a, linkedlist b);

linkedlist LinkedList_Union(linkedlist a, linkedlist b);

void test_linkedlist_operations(void);

void test_linkedlist_operations_more(void);

/**
 * @}
 */

/**
 * @addtogroup Stack
 * @{
 */

status Symbol_IsBalanced(const char* code_segment);

/**
 * @}
 */

/**
 * @addtogroup Queue
 * @{
 */

void Queue_Print(queue q);

void test_queue_operations(void);


/**
 * @}
 */

/**
 * @addtogroup Tree
 * @{
 */

void test_avltree_create(void);

/**
 * @}
 */

/**
 * @addtogroup Hash
 * @{
 */

unsigned int HashWord(const char* key, int table_size);

void test_hash_word(void);


/**
 * @}
 */

/**
 * @addtogroup Heap
 * @{
 */

void test_binheap_operations(void);

void test_leftheap_merge(void);

/**
 * @}
 */

/**
 * @addtogroup Sort
 * @{
 */

void test_sort(void);

/**
 * @}
 */

/**
 * @addtogroup Graph
 * @{
 */

void Graph_Print(graph g);

void test_graph_create(void);

void test_graph_topsort(void);

void test_graph_search(void);

void test_graph_shortestpathlength(void);

void test_graph_minimumspanningtree(void);


/**
 * @}
 */



/**
 * @addtogroup
 * @{
 */

/**
 * @}
 */

#endif //DATASTRUCTURE_TEST_H
