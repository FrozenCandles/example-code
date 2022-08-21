
#ifndef __HASH_H__
#define __HASH_H__

#include "pubdef.h"
#include "linkedlist.h"




//typedef const char* elemtype;

typedef linkedlist hashsep_node;
typedef struct hashsep_table {
    int size;
    hashsep_node* list;
} * hashsep_table;


enum hashquad_status { 
    HASHQUAD_USED, HASHQUAD_EMPTY, HASHQUAD_DELETED };
typedef struct hashquad_node {
    elemtype elem;
    enum hashquad_status status;
} hashquad_node;
typedef struct hashquad_table {
    int size;
    hashquad_node* list;
} * hashquad_table;





#endif /* __HASH_H__ */
