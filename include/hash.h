#ifndef HASH_H_

#define HASH_H_

#include "key.h"

typedef struct hashTable HashTable;

HashTable *HashTable_Create();

void HashTable_Destroy(HashTable *table);

int HashTable_Hash(HashTable *table);

void HashTable_Insert(HashTable *table, Key key);

void HashTable_Remove(HashTable *table, Key key);

#endif // HASH_H_
