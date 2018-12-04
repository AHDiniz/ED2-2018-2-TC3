#ifndef HASH_H_

#define HASH_H_

#include "key.h"

typedef struct hashTable HashTable;

HashTable *HashTable_Create(int size);

void HashTable_Destroy(HashTable *table);

int HashTable_Hash(Key key, HashTable *table);

void HashTable_Insert(HashTable *table, Key key);

void HashTable_Remove(HashTable *table, Key key);

#endif // HASH_H_
