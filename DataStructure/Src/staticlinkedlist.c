

#include "staticlinkedlist.h"

slinkedlist_node linkedspace[SLINKEDLIST_SIZE];


/**
 * @brief remove first node of freespace
 * 
 * @return int 
 */
int SLinkedList_Alloc(void) {
    int pos = linkedspace[0].cursor;
    linkedspace[0].cursor = linkedspace[pos].cursor;
    return pos;
}

/**
 * @brief insert this node to first position of freespace
 * 
 * @param pos 
 */
void SLinkedList_Free(int pos) {
    linkedspace[pos].cursor = linkedspace[0].cursor;
    linkedspace[0].cursor = pos;
}


/**
 * @brief return true if link list is empty
   header position assumed
 * 
 * @param header 
 * @return int 
 */
bool SLinkedList_IsEmpty(int list) {
    return linkedspace[list].cursor == 0;
}


/**
 * @brief return true if this node is the last position
 * 
 * @param posi 
 * @return int 
 */
bool SLinkedList_IsLast(int pos) {
    return linkedspace[pos].cursor == 0;
}


/**
 * @brief return position of elem in link list, 0 if not found
 * 
 * @param elem 
 * @param list 
 * @return int 
 */
int SLinkedList_Find(int list, elemtype elem) {
    int pos = linkedspace[list].cursor;
    while (pos && linkedspace[pos].elem != elem)
        pos = linkedspace[pos].cursor;
    return pos;
}


/**
 * @brief if previous node is not found, last returned
 * 
 * @param elem 
 * @param list 
 * @return int 
 */
int SLinkedList_FindPrevPos(int list, elemtype elem) {
    int prev = linkedspace[list].cursor;
    while (prev && linkedspace[linkedspace[prev].cursor].elem != elem)
        prev = linkedspace[prev].cursor;
    return prev;
}


/**
 * @brief delete first occurence of elem from a list
   assume use of a header node
 * 
 * @param elem 
 * @param list 
 */
status SLinkedList_Remove(int list, elemtype elem) {
    int temp;
    int pos = SLinkedList_FindPrevPos(list, elem);
    if (!SLinkedList_IsLast(pos)) {
        temp = linkedspace[pos].cursor;
        linkedspace[pos].cursor = linkedspace[temp].cursor;
        SLinkedList_Free(temp);
        return 0;
    }
    return 1;
}


status SLinkedList_InsertAfter(int prev, elemtype elem) {
    int temp = SLinkedList_Alloc();
    if (temp == 0) {
        /* fail to allocate memory */
        return 1;
    }
    linkedspace[temp].elem = elem;
    linkedspace[temp].cursor = linkedspace[prev].cursor;
    linkedspace[prev].cursor = temp;
}
