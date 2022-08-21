//
// Created by Hello on 2022-05-09.
//

#ifndef DATASTRUCTURE_BSEARCHTREE_H
#define DATASTRUCTURE_BSEARCHTREE_H

#include <stdio.h>
#include <stdlib.h>

#include "pubdef.h"

typedef struct bsearchtree_node {
    elemtype elem;
    struct bsearchtree_node* left;
    struct bsearchtree_node* right;
} bsearchtree_node, * bsearchtree;


bsearchtree BinSearchTree_Clear(bsearchtree tree);

bsearchtree_node* BinSearchTree_Find(bsearchtree tree, elemtype value);

bsearchtree_node* BinSearchTree_FindMin(bsearchtree tree);

bsearchtree_node* BinSearchTree_FindMax(bsearchtree tree);

bsearchtree BinSearchTree_Insert(bsearchtree tree, elemtype value);

bsearchtree_node* BinSearchTree_Remove(bsearchtree tree, elemtype value);

#endif //DATASTRUCTURE_BSEARCHTREE_H
