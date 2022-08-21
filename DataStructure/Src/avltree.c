
#include "avltree.h"


#define max(x, y) ((x) > (y) ? (x) : (y))


static int AvlTree_Height(const avltree_node* node);

static avltree_node* AvlTree_LeftSingleRotate(avltree_node* k2);

static avltree_node* AvlTree_RightSingleRotate(avltree_node* k1);

static avltree_node* AvlTree_LeftDoubleRotate(avltree_node* k3);

static avltree_node* AvlTree_RightDoubleRotate(avltree_node* k1);

static void AvlTree_PrintNode(avltree_node* node, int depth);



static int AvlTree_Height(const avltree_node* node) {
    if (node == NULL)
        return -1;  // empty tree
    return node->height;
}


avltree_node* AvlTree_FindMax(avltree tree) {
    if (tree != NULL)
        while (tree->right != NULL)
            tree = tree->right;
    return tree;
}

avltree_node* AvlTree_FindMin(avltree tree) {
    if (tree != NULL)
        while (tree->left != NULL)
            tree = tree->left;
    return tree;
}

static avltree_node* AvlTree_LeftSingleRotate(avltree_node* k2) {
    avltree_node* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(AvlTree_Height(k2->left), AvlTree_Height(k2->right)) + 1;
    k1->height = max(AvlTree_Height(k1->left), k2->height) + 1;
    return k1;  // new root
}

static avltree_node* AvlTree_RightSingleRotate(avltree_node* k1) {
    avltree_node* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(AvlTree_Height(k1->left), AvlTree_Height(k1->right)) + 1;
    k2->height = max(AvlTree_Height(k2->right), k1->height) + 1;
    return k2;  // new root
}


static avltree_node* AvlTree_LeftDoubleRotate(avltree_node* k3) {
    k3->left = AvlTree_RightSingleRotate(k3->left);
    return AvlTree_LeftSingleRotate(k3);
}


static avltree_node* AvlTree_RightDoubleRotate(avltree_node* k1) {
    k1->right = AvlTree_LeftSingleRotate(k1->right);
    return AvlTree_RightSingleRotate(k1);
}


avltree AvlTree_Insert(avltree tree, elemtype elem) {
    if (tree == NULL) {    // create and return a one-node tree
        tree = malloc(sizeof(avltree_node));
        if (tree == NULL)  // out of memory
            return NULL;
        tree->elem = elem;
        tree->height = 0;
        tree->left = tree->right = NULL;
    }
    else if (elem < tree->elem) {
        tree->left = AvlTree_Insert(tree->left, elem);
        if (AvlTree_Height(tree->left) - AvlTree_Height(tree->right) == 2) {
            if (elem < tree->left->elem)
                tree = AvlTree_LeftSingleRotate(tree);
            else
                tree = AvlTree_LeftDoubleRotate(tree);
        }
    }    
    else if (elem > tree->elem) {
        tree->right = AvlTree_Insert(tree->right, elem);
        if (AvlTree_Height(tree->right) - AvlTree_Height(tree->left) == 2) {
            if (elem > tree->right->elem)
                tree = AvlTree_RightSingleRotate(tree);
            else
                tree = AvlTree_RightDoubleRotate(tree);
        }
    }
    /* elem is in the tree already */
    tree->height = max(AvlTree_Height(tree->left), AvlTree_Height(tree->right)) + 1;
    return tree;
}


static void AvlTree_PrintNode(avltree_node* node, int depth) {
    if (node && node->height > 0) {
        for (int i = 0; i < depth; i++)
            printf("-");
        printf(" %d\n", node->elem);
    }
}

void AvlTree_Print(avltree tree, int depth) {
    if (tree) {
        AvlTree_Print(tree->left, depth + 1);
        AvlTree_PrintNode(tree, depth);
        AvlTree_Print(tree->right, depth + 1);
    }
}



#ifdef AVL_TREE_HEIGHTKNOWN
int AvlTree_Height(avltree tree) {
    if (tree == NULL)
        return -1;
    return 1 + max(AvlTree_Height(tree->left), AvlTree_Height(tree->right));
}

#endif


#if 0
int main(int argc, char* argv[]) {

    avltree tree = malloc(sizeof(avltree_node));
    if (tree == NULL) {
        exit(EXIT_FAILURE);
    }
    tree->elem = 50;
    tree->left = tree->right = NULL;

    srand(100);
    for (int i = 0; i < 50; i++)
        AvlTree_Insert(tree, rand() % 100);

    AvlTree_Print(tree);

    return 0;
}
#endif


