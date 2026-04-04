#if __STDC_VERSION__ < 202311L
#include <stdbool.h>
#endif

#define VECTOR_TYPE_INPUT 'i'
#include "vector.c"

#define VECTOR_TYPE_INPUT 'b'
#include "vector.c"

#define HASH_TABLE_KEY_TYPE int
#define HASH_TABLE_VALUE_TYPE int

#define VECTOR_NAME_KEY intVector
#define VECTOR_NAME_VALUE intVector

#define HASH_TABLE_NAME HashTable

typedef struct HASH_TABLE_NAME{
    VECTOR_NAME_KEY key;
    VECTOR_NAME_VALUE vector;
    boolVector civilized;
    boolVector retreat;
    int seed;
    int element;
    int retreatOk;
} HASH_TABLE_NAME;

void intializeHashTable(HASH_TABLE_NAME * HashTable, int elementAmount) {
    initializeIntVector(& HashTable -> key, elementAmount);
    initializeIntVector(& HashTable -> vector, elementAmount);

    initializeBoolVector(& HashTable -> civilized, elementAmount);
    for (int i = 0; i < elementAmount; i++) {
        boolAdd(& HashTable -> civilized, false);
    }

    initializeBoolVector(& HashTable -> retreat, elementAmount);
    for (int i = 0; i < elementAmount; i++) {
        boolAdd(& HashTable -> retreat, false);
    }

    HashTable -> seed = rand() % 10;
    HashTable -> element = elementAmount;
}

int hash1(HASH_TABLE_NAME HashTable, HASH_TABLE_KEY_TYPE key) {
    int constant = 0x9e37779b9;
    int destination1 = key + constant + HashTable.seed << 6 + HashTable.seed >> 2;
    int result = HashTable.seed ^ destination1;

    return result;
}

int hash2(HASH_TABLE_NAME HashTable, HASH_TABLE_KEY_TYPE key) {
    int constant = 31;
    int destination1 = key + constant + HashTable.seed << 7 + HashTable.seed >> 1;
    int result = HashTable.seed ^ destination1;

    return result;
}

void addHashTable(HASH_TABLE_NAME * HashTable, HASH_TABLE_KEY_TYPE key, HASH_TABLE_VALUE_TYPE value) {
    int index = ( 3 * hash1(*HashTable, key) + 7 ) % (HashTable -> vector.memoryAmount / sizeof(int));

    while (HashTable -> civilized.array[index] || HashTable -> retreat.array[index]) {
        index = (index + hash2(*HashTable, key) ) % (HashTable -> vector.memoryAmount / sizeof(int));
    }
    HashTable -> key.array[index] = key;
    HashTable -> vector.array[index] = value;
    HashTable -> civilized.array[index] = true;

    HashTable -> element ++;
}

int main() {
    return 0;
}