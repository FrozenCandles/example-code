
#ifndef __DATASTRUCTURE_LINEARLIST_H__
#define __DATASTRUCTURE_LINEARLIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "pubdef.h"


#define LINEARLIST_INIT_SIZE 128

typedef struct {
    int length;
    int size;    // actual allocated size
    elemtype* body;
} linearlist;




#endif // __DATASTRUCTURE_LINEARLIST_H__
