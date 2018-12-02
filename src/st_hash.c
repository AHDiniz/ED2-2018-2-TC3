#include "../include/symbolTable.h"
#include <stdlib.h>

typedef struct list List;
struct list
{
    Key key;
    List *next, *prev;
};

static List *List_Create(Key key)
{
    List *list = malloc(sizeof(*list));
    list->key = key;
    list->next = list->prev = NULL;
    return list;
}

static void List_Destroy(List *list)
{
    if (list == NULL) return;
    List *current = list;
    while (current != NULL)
    {
        List *target = current;
        current = current->next;
        free(target);
    }
}

static void List_Insert(List *list, Key key)
{
    if (list == NULL) return;
    List *end;
    for (end = list; end->next != NULL; end = end->next);
    end->next = List_Create(key);
    end->next->prev = end;
}

static void List_Delete(List *list, Key key)
{
    List *target = list;
    while (target != NULL)
    {
        if (compare(key, target->key) == 0)
        {
            if (target->prev != NULL) target->prev->next = target->next;
            if (target->next != NULL) target->next->prev = target->prev;
            free(target);
            return;
        }
        target = target->next;
    }
}

struct sTable
{
    List **lists;
    int size;
    int max;
};

STable *STable_Create(int max)
{
    STable *table = malloc(sizeof(*table));
    table->lists = malloc(sizeof(*(table->list)) * max);
    for (int i = 0; i < max; i++) table->lists[i] = NULL;
    table->size = 0;
    table->max = max;
    return max;
}

void STable_Destroy(STable *table)
{
    for (int i = 0; i < table->max; i++) List_Destroy(table->lists[i]);
    free(table);
}

int STable_Empty(STable *table)
{
    return table->size == 0;
}

int STable_Size(STable *table)
{
    return table->size;
}

static int STable_Hash(STable *table, Key key)
{
    return table->size + 1;
}

void STable_Insert(STable *table, Key key)
{
    if (table == NULL || table->size == table->max) return;
    int pos = STable_Hash(table, key);
    if (table->lists[i] == NULL) table->lists[i] = List_Create(key);
    else List_Insert(table->lists[i], key);
}
