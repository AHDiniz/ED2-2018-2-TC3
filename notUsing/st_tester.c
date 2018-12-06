#include "../include/symbolTable.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    STable *table = STable_Create(1);

    unsigned char ak[C] = {'a', 'a', 'a', 'a'};
    Key k1 = init_key(ak);

    unsigned char aka[C] = {'a', 'a', 'a', 'b'};
    Key k2 = init_key(aka);

    unsigned char akb[C] = {'a', 'a', 'a', 'c'};
    Key k3 = init_key(akb);

    unsigned char ak1[C] = {'a', 's', 'd', 'f'};
    Key v1 = init_key(ak1);

    unsigned char ak2[C] = {'a', 'a', 'd', 'f'};
    Key v2 = init_key(ak2);
    
    unsigned char ak3[C] = {'a', 'd', 'd', 'f'};
    Key v3 = init_key(ak3);

    printf("Oi\n");

    STable_Insert(table, k1, v1);
    STable_Insert(table, k2, v2);
    STable_Insert(table, k3, v3);

    STable_Print(table);

    print_key_char(STable_GetValue(table, k1));
    printf("\n");
    print_key_char(STable_GetValue(table, k2));
    printf("\n");
    print_key_char(STable_GetValue(table, k3));
    printf("\n");

    STable_Destroy(table);

    return 0;
}

