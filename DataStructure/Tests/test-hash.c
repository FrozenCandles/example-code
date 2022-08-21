
#include <stdio.h>

unsigned int HashWord(const char* key, int table_size) {
    unsigned long val = 0;
    while (*key != '\0')
        val = (val << 5) + * key++;
    return val % table_size;
}

#define HASH_TABLE_SIZE 50021

void test_hash_word(void) {
    printf("%u\n", HashWord("hello", HASH_TABLE_SIZE));
    printf("%u\n", HashWord("world", HASH_TABLE_SIZE));
    printf("%u\n", HashWord("algorithm", HASH_TABLE_SIZE));

}
