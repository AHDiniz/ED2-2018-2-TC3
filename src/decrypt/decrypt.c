/**********************************************************
 * ED2-2018-2-TC3: Password Cracking problem
 * 
 * Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
 * 
 *
 * decrypt.c: decrypt implementations
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../../include/decrypt.h"
#include "../../include/symbolTable.h"
#include "../../include/auxiliar.h"

/**
 * Auxiliar recursive function that sum all possible combinations of T table's keys to find the decrypted passwords and print them:
 *
 * input: pointers to the encrypted key, to the table T, to the table S and to a int vector, a key representing the previous sum, a int representing the current position of T being used and a bool that informs if the key was already compared.
 * output: none.
 * pre condition: binpass with max size of at least N.
 * post condition: encrypted key and T unchanged.
 */
void find(Key *encrypted, Key T[], STable *S, int binpass[], Key pSum, int k, bool change);

/**
 * Auxiliar recursive function that build S:
 *
 * input: pointers to the encrypted key, to the table T, to the table S and to a int vector, a key representing the previous sum, a int representing the current position of T being used and a bool that informs if the key was already compared.
 * output: none.
 * pre condition: binpass with max size of at least N.
 * post condition: encrypted key and T unchanged.
 */
 void build_S(Key T[], STable *S, int binpass[], Key pSum, int k, bool change);

void decrypt(Key encrypted, Key *T)
{
    int binpass[N] = { 0 };                             // Binary password.
    unsigned char *c = convert(binpass);                // Initial key. (all bits = 0)

    STable *S = STable_Create(pow(2,K));                // Initializing S.

    build_S(T, S, binpass, init_key(c), N-K, false);    // Building S with the K last positions of T.

    find(&encrypted, T, S, binpass, init_key(c), 0, true);

    STable_Destroy(S);
    free(c);
}


void find(Key *encrypted, Key T[], STable *S, int binpass[], Key pSum, int k, bool change)
{
    // Checking previous sum:
    if (change && compare(pSum, *encrypted) == 0)
    {
        unsigned char *c = convert(binpass);
        printf("%s\n", c);                      // Printing the sum if it matches the encrypted key.
        free(c);
    }
    if (k == N - K) // Cutoff condition.
    {
        Key subt = sub(*encrypted, pSum);
        STable_PrintKey(S, subt, binpass);
        return;
    }
    if (k >= N) // Stop condition (for safety).
    {
        return;
    }

    // Checking all combinations with previous sum, without the current key (change is false because pSum was checked previously).
    find(encrypted, T, S, binpass, pSum, k + 1, false);

    Key sum = add(pSum, T[k]);  // Adding current key to the sum.
    binpass[k] = 1;             // Marking key as added in the binary vector.

    // Recursively checking all combinations with the new sum:
    find(encrypted, T, S, binpass, sum, k + 1, true);

    binpass[k] = 0; // Unchecking the current key to restart it's condition.
}

void build_S(Key T[], STable *S, int binpass[], Key pSum, int k, bool change)
{
    // Adding previous sum, if it changes:
    if (change)
    {
        unsigned char *c = convert(binpass);
        STable_Insert(S, pSum, init_key(c));
        free(c);
    }
    if (k >= N) // Stop condition.
    {
        return;
    }

    // Checking all combinations with previous sum, without the current key (change is false because pSum was checked previously).
    build_S(T, S, binpass, pSum, k + 1, false);

    Key sum = add(pSum, T[k]);  // Adding current key to the sum.
    binpass[k] = 1;             // Marking key as added in the binary vector.

    // Recursively checking all combinations with the new sum:
    build_S(T, S, binpass, sum, k + 1, true);

    binpass[k] = 0; // Unchecking the current key to restart it's condition.
}
