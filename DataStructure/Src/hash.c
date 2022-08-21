
#include "hash.h"


typedef unsigned int index;

//index HashWord(const char* key, int table_size) {
//    unsigned long val = 0;
//    while (*key != '\0')
//        val = (val << 5) + * key++;
//    return val % table_size;
//}

/**
 * @brief 
 * see https://www.geeksforgeeks.org/program-to-find-the-next-prime-number/
 * @param n 
 * @return true 
 * @return false 
 */
bool IsPrime(int n) {
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;
    // This is checked so that we can skip 
    // middle five numbers in below loop
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
           return false;
    return true;
}
 
/**
 * @brief Function to return the smallest
 * prime number greater than n
 * @param n 
 * @return int 
 */
int NextPrime(int n) {
    // Base case
    if (n <= 1)
        return 2;
    int prime = n;
    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (1) {
        prime++;
        if (IsPrime(prime))
            break;
    }
    return prime;
}


hashsep_table HashSepTable_New(int size) {
    hashsep_table table = malloc(sizeof(struct hashsep_table));
    if (table == NULL)
        return NULL;      // out of memory
    table->size = size;
    table->list = malloc(sizeof(hashsep_node) * table->size);
    if (table->list == NULL)
        return NULL;      // out of memory
    /* table->list = malloc(table->size * sizeof(linkedlist_node)); */
    for (int i = 0; i < table->size; i++) {
        table->list[i] = malloc(sizeof(linkedlist_node));
        if (table->list[i] == NULL)
            return NULL;  // out of memory
        table->list[i]->next = NULL;
    }    
    return table;
}


index Hash(elemtype key, int table_size) {
    return rand() % table_size;
}

static bool Equals(elemtype key1, elemtype key2) {
    return key1 == key2;
}

static void Assign(elemtype* variable, elemtype value) {
    *variable = value;
}


linkedlist_node* HashSepTable_Find(hashsep_table table, elemtype key) {
    linkedlist list = table->list[Hash(key, table->size)];
    linkedlist_node* node = list->next;
    while (node != NULL && !Equals(node->elem, key))
        node = node->next;
    return node;
}


status HashSepTable_Insert(hashsep_table table, elemtype key) {
    linkedlist_node* node = HashSepTable_Find(table, key);
    if (node == NULL) {   // key not found
        linkedlist_node* new_node = malloc(sizeof(linkedlist_node));
        if (new_node == NULL)
            return 2;     // out of memory
        linkedlist list = table->list[Hash(key, table->size)];
        new_node->next = list->next;
        Assign(&new_node->elem, key);
        list->next = new_node;
        return 0;
    }
    return 1;
}



hashquad_table HashQuadTable_New(int size) {
    hashquad_table table = malloc(sizeof(struct hashquad_table));
    if (table == NULL)
        return NULL;  // out of memory
    table->size = size;
    table->list = malloc(sizeof(hashquad_node) * table->size);
    if (table->list == NULL)
        return NULL;  // out of memory
    for (int i = 0; i < table->size; i++)
        table->list[i].status = HASHQUAD_EMPTY;
    return table;
}



index HashQuadTable_Find(hashquad_table table, elemtype key) {
    index pos = Hash(key, table->size);
    int collision = 0;
    while (table->list[pos].status != HASHQUAD_EMPTY &&
           !Equals(table->list[pos].elem, key)) {
            pos += 2 * ++collision - 1;
            if (pos >= table->size)
                pos -= table->size;
    }
    return pos;
}


status HashQuadTable_Insert(hashquad_table table, elemtype key) {
    index pos = HashQuadTable_Find(table, key);
    if (table->list[pos].status != HASHQUAD_USED) {
        table->list[pos].status = HASHQUAD_USED;
        Assign(&table->list[pos].elem, key);
        return 0;
    }
    return 1;
}


status HashQuadTable_Remove(hashquad_table table, elemtype key) {
    index pos = HashQuadTable_Find(table, key);
    if (table->list[pos].status != HASHQUAD_DELETED) {
        table->list[pos].status = HASHQUAD_DELETED;
        return 0;
    }
    return 1;
}


hashquad_table HashQuadTable_Rehash(hashquad_table table) {
    int old_size = table->size;
    hashquad_node* old_list = table->list;
    table = HashQuadTable_New(NextPrime(old_size * 2));
    for (int i = 0; i < old_size; i++)
        if (old_list[i].status != HASHQUAD_USED)
            HashQuadTable_Insert(table, old_list[i].elem);
    free(old_list);
    return table;
}

