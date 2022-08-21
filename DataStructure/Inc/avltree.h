
#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include <stdlib.h>
#include <stdio.h>

#include "pubdef.h"

typedef struct avltree_node {
    elemtype elem;
    struct avltree_node* left;
    struct avltree_node* right;
    int height;
} avltree_node, * avltree;


#define avltree_print(avl) AvlTree_Print(avl, 0)


avltree_node* AvlTree_FindMax(avltree tree);

avltree_node* AvlTree_FindMin(avltree tree);

avltree AvlTree_Insert(avltree tree, elemtype elem);

void AvlTree_Print(avltree tree, int depth);

#endif /* __AVLTREE_H__ */
