//
// Created by Hello on 2022-05-09.
//
#include "bsearchtree.h"





bsearchtree BinSearchTree_Clear(bsearchtree tree) {
    if (tree != NULL) {
        BinSearchTree_Clear(tree->left);
        BinSearchTree_Clear(tree->right);
        free(tree);
    }
    return NULL;
}

/**
 * find a node from the given search tree
 * return NULL if not found
 * @param tree
 * @param value
 * @return
 */
bsearchtree_node* BinSearchTree_Find(bsearchtree tree, elemtype value) {
    if (tree == NULL)
        return NULL;
    if (value < tree->elem)
        return BinSearchTree_Find(tree->left, value);
    else if (value > tree->elem)
        return BinSearchTree_Find(tree->right, value);
    else
        return tree;
}

bsearchtree_node* BinSearchTree_FindMin(bsearchtree tree) {
    if (tree == NULL)
        return NULL;
    else if (tree->left == NULL)
        return tree;
    else
        return BinSearchTree_FindMin(tree->left);
}

bsearchtree_node* BinSearchTree_FindMax(bsearchtree tree) {
    if (tree != NULL)
        while (tree->right != NULL)
            tree = tree->right;
    return tree;
}





bsearchtree BinSearchTree_Insert(bsearchtree tree, elemtype value) {
    if (tree == NULL) {  // empty tree, should create first
        tree = malloc(sizeof(bsearchtree_node));
        if (tree == NULL)
            return NULL;  // fail to allocate memory
        tree->elem = value;
        tree->left = tree->right = NULL;
    }
    else if (value < tree->elem)
        tree->left = BinSearchTree_Insert(tree->left, value);
    else if (value > tree->elem)
        tree->right = BinSearchTree_Insert(tree->right, value);
    return tree;  // value is already in the tree
}

bsearchtree_node* BinSearchTree_Remove(bsearchtree tree, elemtype value) {
    if (tree == NULL)
        return NULL;              // element not found
    bsearchtree_node* temp;
    if (value < tree->elem)       // go left
        tree->left = BinSearchTree_Remove(tree->left, value);
    else if (value > tree->elem)  // go right
        tree->right = BinSearchTree_Remove(tree->right, value);
    else if (tree->left && tree->right) {  // element found with 2 children
        /* replace by min value in right subtree */
        temp = BinSearchTree_FindMin(tree->right);
        tree->elem = temp->elem;
        tree->right = BinSearchTree_Remove(tree->right, tree->elem);
    }
    else {  // element found with 0 or 1 children
        temp = tree;
        if (tree->left == NULL)
            tree = tree->right;
        else if (tree->right == NULL)
            tree = tree->left;
        free(temp);
    }
    return tree;
}
