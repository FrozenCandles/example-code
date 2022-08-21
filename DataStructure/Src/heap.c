

#include "heap.h"


binheap* BinHeap_New(int size) {
    binheap* heap = malloc(sizeof(binheap));
    if (heap == NULL)
        return NULL;  // out of memory
    heap->body = malloc(sizeof(elemtype) * (size + 1));
    if (heap->body == NULL)
        return NULL;  // out of memory
    heap->size = size;
    heap->length = 0;
    heap->body[0] = HEAP_MIN_ELEM;
    return heap;
}

bool BinHeap_IsEmpty(binheap* heap) {
    return heap->length == 0;
}

bool BinHeap_IsFull(binheap* heap) {
    return heap->length == heap->size;
}


status BinHeap_Insert(binheap* heap, elemtype elem) {
    if (BinHeap_IsFull(heap))
        return 1;  // out of space
    int i;
    for (i = ++heap->length; heap->body[i / 2] > elem; i /= 2)
        heap->body[i] = heap->body[i / 2];
    heap->body[i] = elem;
    return 0;
}




elemtype BinHeap_RemoveMin(binheap* heap) {
    if (BinHeap_IsEmpty(heap))
        return heap->body[0];   // empty priority queue
    elemtype minimum = heap->body[1];
    elemtype last = heap->body[heap->length--];
    int i = 1;
    while (i * 2 <= heap->size) {
        int child = i * 2;      // find smaller child
        if (child != heap->length &&
            heap->body[child + 1] < heap->body[child])
            child++;
        if (last > heap->body[child])
            heap->body[i] = heap->body[child];
        else
            break;
        i = child;
    }
    heap->body[i] = last;
    return minimum;
}


void BinHeap_PrintArray(binheap* heap) {
    for (int i = 1; i < heap->length; i++)
        printf("%d, ", heap->body[i]);
    putchar('\n');
}

uint32_t next_pow2(uint32_t v) {
    --v;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    return ++v;
}

static int pow2i(int a) {
    int r = 1;
    while (a--) {
        r *= 2;
    }
    return r;
}

/**
 * stolen from https://stackoverflow.com/questions/65140349/printing-binary-heap-in-tree-format-c-language
 * @param arr
 * @param length
 */
void Array_PrintTree(const elemtype *arr, size_t length) {
    int longest_digits = 0;
    int tree_depth = 0;
    int pos = 0;
    int depth = 0;
    for (size_t i = 0; i < length; ++i) {
        if (arr[i] != -1) {
            const int len = snprintf(NULL, 0, "%d", arr[i]);
            if (longest_digits < len)
                longest_digits = len;
        }
        if (pos == 0) {
            tree_depth++;
            pos = pow2i(depth++);
        }
        pos--;
    }
    //printf("%d %d\n", longest_digits, tree_depth);
    pos = 0;
    depth = 0;
    const int additional_offset = 3;
    int max_width = pow2i(tree_depth) * (longest_digits + additional_offset);
    for (size_t i = 0; i < length; ++i) {
        const bool first = pos == 0;
        if (first) {
            pos = pow2i(depth);
            depth++;
        }
        const int count_elems = pow2i(depth);
        const int chunk = max_width / count_elems;
        const int width = chunk + (first ? -chunk/2 : 0);
        const int pre_spaces = width - longest_digits;

        printf("%*s", pre_spaces, "");
        if (arr[i] == -1)
            printf("%*s", longest_digits, "-");
        else
            printf("%*d", longest_digits, arr[i]);
        if (pos == 1)
            printf("\n");

        pos--;
    }
}


void BinHeap_PrintTree(binheap* heap) {
#ifndef BINHEAP_BETTER_PRINT
    uint32_t width = next_pow2(heap->length / 2);
    uint32_t count = 1;
    for (uint32_t elems = 1; elems <= width; elems <<= 1) {
        for (int i = 0; i < elems; i++) printf("%d ", heap->body[count + i]);
        count += elems;
        putchar('\n');
    }
    putchar('\n');
#else
    Array_PrintTree(heap->body + 1, heap->length);
    putchar('\n');
#endif
}




void LeftHeap_SwapChildren(leftheap heap) {
    leftheap_node* tmp;
    tmp = heap->left;
    heap->left = heap->right;
    heap->right = tmp;
}


static leftheap _LeftHeap_Merge(leftheap heap_A, leftheap heap_B) {
    if (heap_A->left == NULL)
        heap_A->left = heap_B;
    else {
        heap_A->right = LeftHeap_Merge(heap_A->right, heap_B);
        if (heap_A->left->Npl < heap_A->right->Npl)
            LeftHeap_SwapChildren(heap_A);
        heap_A->Npl = heap_A->right->Npl + 1;
    }
    return heap_A;
}


leftheap LeftHeap_Merge(leftheap heap_A, leftheap heap_B) {
    if (heap_A == NULL) return heap_B;
    if (heap_B == NULL) return heap_A;
    if (heap_A->elem < heap_B->elem)
        return _LeftHeap_Merge(heap_A, heap_B);
    else
        return _LeftHeap_Merge(heap_B, heap_A);
}


leftheap LeftHeap_Insert(leftheap heap, elemtype elem) {
    leftheap_node* node = malloc(sizeof(leftheap_node));
    if (node == NULL)
        return NULL;  // out of space
    node->elem = elem;
    node->left = node->right = NULL;
    return LeftHeap_Merge(heap, node);
}


bool LeftHeap_IsEmpty(leftheap heap) {
    return heap == NULL;
}


/**
 * @brief 
 * To get the minimum, use FindMin()
 * @param heap 
 * @return leftheap new tree
 */
leftheap LeftHeap_RemoveMin(leftheap heap) {
    if (LeftHeap_IsEmpty(heap))
        return heap;  // empty heap
    leftheap left  = heap->left;
    leftheap right = heap->right;
    free(heap);
    return LeftHeap_Merge(left, right);
}


elemtype LeftHeap_FindMin(leftheap heap){
    if(!LeftHeap_IsEmpty(heap))
        return heap->elem;
    /* leftist heap is empty */
    return 0;  // return value to avoid warning
}


static void LeftHeap_PrintNode(leftheap_node* node, int depth) {
    if (node/* && node->height > 0*/) {
        for (int i = 0; i < depth; i++)
            printf("-");
        printf(" %d\n", node->elem);
    }
}

void LeftHeap_Print(leftheap tree, int depth) {
    if (tree) {
        LeftHeap_Print(tree->left, depth + 1);
        LeftHeap_PrintNode(tree, depth);
        LeftHeap_Print(tree->right, depth + 1);
    }
}

