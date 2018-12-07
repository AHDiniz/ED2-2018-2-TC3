#ifndef SYMBOL_TABLE_H_

#define SYMBOL_TABLE_H_

#include "key.h"

typedef struct sTable STable;

STable *STable_Create(int max);

void STable_Destroy(STable *table);

int STable_Empty(STable *table);

int STable_Size(STable *table);

void STable_Insert(STable *table, Key key, Key value);

int STable_Contains(STable *table, Key key);

void STable_Print(STable *table);

void STable_PrintKey(STable *table, Key key, int *binpass);

#endif // SYMBOL_TABLE_H_
