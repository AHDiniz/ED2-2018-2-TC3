#include "../include/symbolTable.h"

int main(int argc, char *argv[])
{
    STable *table = STable_Create(123);

    unsigned char ak1[C] = {'a', 's', 'd', 'f', 'g'};
    Key k1 = init_key(ak1);

    unsigned char ak2[C] = {'a', 'a', 'd', 'f', 'g'};
    Key k2 = init_key(ak2);
    
    unsigned char ak3[C] = {'a', 'd', 'd', 'f', 'g'};
    Key k3 = init_key(ak3);

    printf("Oi\n");

    STable_Insert(table, k1);
    STable_Insert(table, k2);
    STable_Insert(table, k3);

    STable_Print(table);

    STable_Destroy(table);

    return 0;
}

