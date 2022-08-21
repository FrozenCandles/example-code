//
// Created by Hello on 2022-05-05.
//

#include "linkedlist.h"


/**
 * Return true if the linked list is empty
 * @param header
 * @return
 */
bool LinkedList_IsEmpty(linkedlist list) {
    return list->next == NULL;
}

/**
 * Return true if current node is the last position
 * @param node
 * @return
 */
bool LinkedList_IsLast(linkedlist list) {
    return list->next == NULL;
}

/**
 * Return a node in certain position, NULL if not found
 * @param value
 * @param node
 * @return
 */
linkedlist_node* LinkedList_GetNode(linkedlist_node* node, elemtype value) {
    linkedlist_node* nxt = node->next;
    while (nxt != NULL && nxt->elem != value)
        nxt = nxt->next;
    return nxt;
}

/**
 * if previous node is not found, last returned
 * @param value
 * @param list
 * @return
 */
linkedlist_node* LinkedList_GetPrevNode(linkedlist list, elemtype value) {
    linkedlist_node* prev = list;
    while (prev->next != NULL && prev->next->elem != value)
        prev = prev->next;
    return prev;
}

/**
 * delete first occurence of element in linked list
 * @param value
 * @param list
 */
status LinkedList_Remove(linkedlist list, elemtype value) {
    linkedlist_node* prev = LinkedList_GetPrevNode(list, value);
    if (!LinkedList_IsLast(prev)) {
        linkedlist_node* temp = prev->next;
        prev->next = temp->next;  // bypass deleted cell
        free(temp);
        return 0;
    }
    return 1;
}


/**
 * @brief delete (index)th element
 * 
 * @param list 
 * @param index 
 * @param ret 
 * @return status 
 */
status LinkedList_RemoveAt(linkedlist list, int index, elemtype* ret) {
    linkedlist_node* node = list;
    int i = 0;
    while (node->next && i < index - 1) {  // find (index)th element
        node = node->next;
        i++;
    }
    if (!(node->next) || i > index - 1) {
        /* incorrect deleting position */
        return 1;
    }
    linkedlist_node* temp = node->next;
    node->next = temp->next;  // bypass deleted cell
    *ret = temp->elem;
    free(temp);
    return 0;

}

/**
 * insert after prev, header implementation assumed
 * @param value
 * @param prev
 */
status LinkedList_InsertAfter(linkedlist_node* prev, elemtype value) {
    linkedlist_node* temp = malloc(sizeof(linkedlist_node));
    if (temp == NULL) {
        return 1;  // fail to allocate memory for node
    }
    temp->elem = value;
    temp->next = prev->next;
    prev->next = temp;
    return 0;
}


void LinkedList_Print(linkedlist_node* header) {
    int count = 0;
    linkedlist_node* temp = header->next;
    printf("LinkedList { ");
    while (temp) {
        printf("%d > ", temp->elem);
        temp = temp->next;
        count++;
    }
    printf("|| }, size=%zu", count);
}


void LinkedList_Println(linkedlist_node* header) {
    int count = 0;
    linkedlist_node* temp = header->next;
    printf("LinkedList { ");
    while (temp) {
        printf("%d > ", temp->elem);
        temp = temp->next;
        count++;
    }
    printf("|| }, size=%zu\n", count);
}

/**
 * delete link list and each element
 * @param header
 */
void LinkedList_Clear(linkedlist_node* header) {
    linkedlist_node* pres, * temp;
    pres = header->next;
    header->next = NULL;
    while (pres != NULL) {
        temp = pres->next;
        free(pres);
        pres = temp;
    }
}


linkedlist LinkedList_FromArray(const elemtype values[], int length) {
    linkedlist_node* header = malloc(sizeof(linkedlist_node));  // create header node
    linkedlist_node* pres = header;
    for (int i = 0; i < length; i++) {    // create some nodes
        linkedlist_node* temp = malloc(sizeof(linkedlist_node));
        if (temp && pres) {
            temp->elem = values[i];
            temp->next = NULL;
            pres->next = temp;
            pres = pres->next;
        }
    }
    return header;
}


linkedlist LinkedList_New(void) {
    linkedlist_node* header = malloc(sizeof(linkedlist_node));
    return header;
}


linkedlist LinkedList_Reverse(linkedlist list) {
    linkedlist_node* header = malloc(sizeof(linkedlist_node));
    if (!header)
        return NULL;
    header->next = NULL;
    while (list = list->next) {
        LinkedList_InsertAfter(header, list->elem);
    }
    return header;
}


/**
 * Return true if current node is the header position
 * @param node
 * @return
 */
bool DuLinkedList_IsHeader(dulinkedlist_node* node) {
    return node->prev == NULL;
}

/**
 * insert after prior, header implementation assumed
 * @param prev
 * @param value
 */
status DuLinkedList_InsertAfter(dulinkedlist_node* previous, elemtype value) {
    dulinkedlist_node* next = previous->next;
    dulinkedlist_node* temp = malloc(sizeof(dulinkedlist_node));
    if (temp == NULL)
        return 1;
    temp->elem = value;
    temp->next = next;  // adjusting between this and next
    next->prev = temp;
    temp->prev = previous;   // adjusting between this and prev
    previous->next = temp;
    return 0;
}

/**
 * delete right first occurence of element in linked list
 * @param last
 * @param value
 */
void DuLinkedList_DeleteLast(dulinkedlist_node* last, elemtype value) {
    dulinkedlist_node* tmp = last;
    while (tmp && tmp->elem != value)
        tmp = tmp->prev;
    if (tmp && !DuLinkedList_IsHeader(tmp)) {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        free(tmp);
    }
}



clinkedlist CircularLinkedList_FromArray(const elemtype values[], int length) {
    clinkedlist header = malloc(sizeof(clinkedlist_node));  // create header node
    clinkedlist pres = header;
    for (int i = 0; i < length; i++) {    // create some nodes
        clinkedlist temp = malloc(sizeof(clinkedlist_node));
        if (temp && pres) {
            temp->elem = values[i];
            temp->next = NULL;
            pres->next = temp;
            pres = pres->next;
        }
    }
    pres->next = header;  // connect the header node and the tail node
    return header;
}
