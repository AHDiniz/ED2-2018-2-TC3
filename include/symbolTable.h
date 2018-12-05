#ifndef SYMBOL_TABLE_H_

#define SYMBOL_TABLE_H_

#include "key.h"

typedef struct sTable STable;

// typedef void (*STable_Manipulate)(void*,void*) callback; 

STable *STable_Create(int max);

void STable_Destroy(STable *table);

int STable_Empty(STable *table);

int STable_Size(STable *table);

void STable_Insert(STable *table, Key key);

int STable_Contains(STable *table, Key key);

void STable_Delete(STable *table, Key key);

void STable_Print(STable *table);

// IMPLEMENTE ISSO:
// void STable_RunThrougth(STable *table, void *data, callback);

#endif // SYMBOL_TABLE_H_
