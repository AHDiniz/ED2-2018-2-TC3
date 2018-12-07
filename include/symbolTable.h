#ifndef SYMBOL_TABLE_H_

#define SYMBOL_TABLE_H_

#include "key.h"

typedef struct sTable STable;

STable *STable_Create(int max);

void STable_Destroy(STable *table);

int STable_Empty(STable *table);

int STable_Size(STable *table);

void STable_Insert(STable *table, int key, Key value);

int STable_Contains(STable *table, int key);

void STable_Print(STable *table);

Key STable_GetValue(STable *table, int key);

#endif // SYMBOL_TABLE_H_
