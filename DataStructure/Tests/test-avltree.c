//
// Created by Hello on 2022-08-06.
//

#include <stdlib.h>

#include "avltree.h"

void test_avltree_create(void) {

    srand(10);

    avltree tree = malloc(sizeof(avltree_node));
    tree->elem = 50;
    tree->left = tree->right = NULL;
    for (int i = 0; i < 30; i++)
        AvlTree_Insert(tree, rand() % 100);

    avltree_print(tree);
}

