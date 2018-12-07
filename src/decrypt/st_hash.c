#include "../../include/symbolTable.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct list List;
struct list
{
    int key;
    Key value;
    List *next, *prev;
};

static List *List_Create(int key, Key value)
{
    List *list = malloc(sizeof(*list));
    list->key = key;
    list->value = value;
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

static void List_Insert(List *list, int key, Key value)
{
    if (list == NULL) return;
    List *end;
    for (end = list; end->next != NULL; end = end->next);
    end->next = List_Create(key, value);
    end->next->prev = end;
}

static void List_Delete(List *list, int key)
{
    List *target = list;
    while (target != NULL)
    {
        if (key == target->key)
        {
            if (target->prev != NULL) target->prev->next = target->next;
            if (target->next != NULL) target->next->prev = target->prev;
            free(target);
            return;
        }
        target = target->next;
    }
}

static Key List_GetValue(List *list, int key)
{
    if (list == NULL) return;
    List *aux;
    for (aux = list; aux != NULL; aux = aux->next)
    {
        if (aux->key == key)
            return aux->value;
    }
    return;
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
    table->lists = malloc(sizeof(*(table->lists)) * max);
    for (int i = 0; i < max; i++) table->lists[i] = NULL;
    table->size = 0;
    table->max = max;
    return table;
}

void STable_Destroy(STable *table)
{
    for (int i = 0; i < table->max; i++) List_Destroy(table->lists[i]);
    free(table->lists);
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

static int STable_Hash(STable *table, int j)
{
    // int j = 0;
    // for(int i = 0; i < N; i++)
    // {
    //     j += bit(key, N-1-i) << i;
    // }
    return j % table->max;
}

void STable_Insert(STable *table, int key, Key value)
{
    if (table == NULL) return;
    int pos = STable_Hash(table, key);
    if (table->lists[pos] == NULL) table->lists[pos] = List_Create(key, value);
    else List_Insert(table->lists[pos], key, value);
    table->size += 1;
}

int STable_Contains(STable *table, int key)
{
    int result = 0;
    for (int i = 0; i < table->max; i++)
    {
        if (result) break;
        if (table->lists[i] != NULL)
        {
            List *current;
            for (current = table->lists[i]; current != NULL; current = current->next)
                if (current->key != key)
                    break;
            result = current != NULL;
        }
    }
    return result;
}

void STable_Print(STable *table)
{
    for (int i = 0; i < table->max; i++)
    {
        if (table->lists[i] != NULL)
        {
            int s=0;
            for (List *current = table->lists[i]; current != NULL; current = current->next)
            {
                // print_key_char(current->key);
                printf("%d", current->key);
                printf(" ");
                s++;
            }
            printf("(%d)", s);
        }else 
            printf("(0)");
    }
    printf("\nsize= %d\n", table->size);
}

Key STable_GetValue(STable *table, int key)
{
    if (table == NULL) return;
    int pos = STable_Hash(table, key);
    if (table->lists[pos] == NULL) return;
    return List_GetValue(table->lists[pos], key);
}
