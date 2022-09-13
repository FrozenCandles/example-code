
#include "stack.h"


/**
 *
 * @param s
 */
void Stack_Clear(stack* s) {
    s->topptr = STACK_NULLTOP;
}


stack* Stack_New(int capacity) {
    if (capacity < STACK_MINLEN) {
        /* size too small */
        return NULL;    
    }
    stack* s = malloc(sizeof(stack));
    if (s == NULL) {
        /* raise warning */
        return NULL;
    }
    s->body = malloc(sizeof(elemtype) * capacity);
    if (s->body == NULL) {
        /* raise warning */
        return NULL;
    }
    s->topptr = STACK_NULLTOP;
    s->size = capacity;
    return s;
}

bool Stack_IsFull(stack* s) {
    return s->topptr >= s->size - 1;
}

status Stack_Push(elemtype value, stack* s) {
    if (Stack_IsFull(s))
        return 1;  // stack full
    s->body[++s->topptr] = value;
    return 0;
}

bool Stack_IsEmpty(stack* s) {
    return s->topptr == STACK_NULLTOP;
}
status Stack_Pop(stack* s) {
    if (Stack_IsEmpty(s)) {
        return 1;  // stack empty
    }
    s->topptr--;
    return 0;
}

void Stack_Delete(stack* s) {
    if (s != NULL) {
        free(s->body);
        free(s);
    }
}


elemtype Stack_Top(stack* s) {
    if (!Stack_IsEmpty(s))
        return s->body[s->topptr];
    /* raise warning */
    return 0; // return value to avoid warning
}

elemtype Stack_PopTop(stack* s) {
    if (!Stack_IsEmpty(s))
        return s->body[s->topptr--];
    /* stack empty */
    return 0;  // return value to avoid warning
}






bool LinkedStack_IsEmpty(linkedstack s) {
    return s->next == NULL;
}

status LinkedStack_Push(linkedstack s, elemtype value) {
    linkedlist_node* cell = malloc(sizeof(linkedlist_node));
    if (cell == NULL)
        return 1;  // stack (memory) full
    cell->elem = value;
    cell->next = s->next;
    s->next = cell;
    return 0;
}

status LinkedStack_Pop(linkedstack s) {
    if (LinkedStack_IsEmpty(s))
        return 1;
    linkedlist_node* first = s->next;
    s->next = s->next->next;
    free(first);
    return 0;
}

elemtype LinkedStack_Top(linkedstack s) {
    if (!LinkedStack_IsEmpty(s))
        return s->next->elem;
    /* empty stack */
    return 0;  // return to avoid warning
}

status LinkedStack_Clear(linkedstack s) {
    if (s == NULL)
        return 1;  // not created
    else
        while (!LinkedStack_IsEmpty(s))
            LinkedStack_Pop(s);
    return 0;
}
