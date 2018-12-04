#include "../include/hash.h"
#include <stdlib.h>

struct hashTable
{
    Key *keys;
    int size;
};

HashTable *HashTable_Create(int size)
{
    HashTable *table = (HashTable *) malloc(sizeof(*table));

    table->keys = (Key *) malloc(sizeof(Key) * size);
    table->size = size;

    for (int i = 0; i < size; i++)
        table->keys[i] = {' '};

    return table;
}

void HashTable_Destroy(HashTable *table)
{
    free(table->keys);
    free(table);
}

int HashTable_Hash(Key key, HashTable *table)
{
    int pos = 0;

    for (int i = 0; i < C; i++)
    {
        pos += key.digit[i];
    }

    return pos % table->size;
}

void HashTable_Insert(HashTable *table, Key key)
{
    int pos = HashTable_Hash(key, table);

    while (table->keys[pos].digit[0] != ' ')
        pos++;
    
    table->keys[pos] = key;
}

void HashTable_Remove(HashTable *table, Key key)
{
    
}
