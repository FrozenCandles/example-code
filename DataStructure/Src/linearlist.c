
#include "linearlist.h"


status Linearlist_Init(linearlist* l, int size) {
    l->body = (elemtype*) malloc(sizeof(elemtype) * size);
    if (l->body == NULL)
        return 1;
    l->length = 0;
    l->size = size;
    return 0;
}

/**
 * @brief construct a linearlist from an array of elements
 * 
 * @param array 
 * @param size 
 * @return linearlist*
 */
linearlist* Linearlist_FromArray(elemtype* array, int size) {
    linearlist* list = (linearlist*) malloc(sizeof(linearlist));
    list->body = (elemtype*) malloc(sizeof(elemtype) * size);
    if (!list->body) {
        /* fail to allocate memory for table */
        return NULL;
    }
    for (int i = 0; i < size; i++)
        list->body[i] = array[i];
    list->length = size;
    list->size = size;
    return list;
}


status Linearlist_InsertAt(linearlist* list, elemtype elem, int index) {
    if (index > list->length + 1 || index < 1) {
        /* inappropriate inserting position */
        return 1;
    }
    if (list->length == list->size) {
        /* have no extra storage space for element */
        return 2;
    }
    for (int i = list->length - 1; i >= index; i--) 
        list->body[i + 1] = list->body[i];
    list->body[index] = elem;
    list->length++;
    return 0;
}


status Linearlist_RemoveAt(linearlist* list, int index) {
    if (index > list->length + 1 || index < 1) {
        /* inappropriate position */
        return 1;
    }
    for (int i = index; i < list->length; i++)
        list->body[i] = list->body[i + 1];
    list->length--;
    return 0;
}


inline void Linearlist_UpdateAt(linearlist* list, int index, elemtype newvalue) {
    list->body[index] = newvalue;
}


int Linearlist_Find(linearlist* list, elemtype elem) {
    for (int i = 0; i < list->length; i++)
        if (elem == list->body[i])
            return i;
    return -1;
}


inline int Linearlist_GetLength(linearlist* list) {
    return list->length;
}

inline int Linearlist_GetSize(linearlist* list) {
    return list->size;
}


