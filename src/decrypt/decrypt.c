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
#include <math.h>

#include "../../include/decrypt.h"
#include "../../include/symbolTable.h"

#define K (N/2)

// typedef struct
// {
//     Key encrypted;
//     Key pSum;
// } key_enc;

/**
 * Auxiliar callback function:
 *
 * input: pointer to a Key and to the encrypted key.
 * output: none.
 * pre condition: none.
 * post condition: inputs unchanged.
 */
// void find_Key(void *, void *);

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
    int binpass[N] = { 0 };                     // Binary password.
    unsigned char *c = convert(binpass);        // Initial key. (all bits = 0)
    STable *S = STable_Create(pow(2,K));

    build_S(T, S, binpass[], init_key(c), N-K, true);

    find(&encrypted, T, S, binpass, init_key(c), 0, true);

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
    // if (k > N - K) // Cutoff condition.
    // {
    //     STable_RunThrougth(STable *table, void *data, callback);
    // }
    if (k >= N) // Stop condition.
    {
        return;
    }

    // Checking all combinations with previous sum, without the current key (change is false because pSum was checked previously).
    force(encrypted, T, S, binpass, pSum, k + 1, false);

    Key sum = add(pSum, T[k]);  // Adding current key to the sum.
    binpass[k] = 1;             // Marking key as added in the binary vector.

    // Recursively checking all combinations with the new sum:
    force(encrypted, T, S, binpass, sum, k + 1, true);

    binpass[k] = 0; // Unchecking the current key to restart it's condition.
}

void build_S(Key T[], STable *S, int binpass[], Key pSum, int k, bool change)
{
    // Adding previous sum, if it changes:
    if (change)
    {
        unsigned char *c = convert(binpass);
        STable_Insert(S, init_key(c), pSum);
        free(c);
    }
    if (k >= N) // Stop condition.
    {
        return;
    }

    // Checking all combinations with previous sum, without the current key (change is false because pSum was checked previously).
    force(T, S, binpass, pSum, k + 1, false);

    Key sum = add(pSum, T[k]);  // Adding current key to the sum.
    binpass[k] = 1;             // Marking key as added in the binary vector.

    // Recursively checking all combinations with the new sum:
    force(T, S, binpass, sum, k + 1, true);

    binpass[k] = 0; // Unchecking the current key to restart it's condition.
}

// void find_Key(void *key, void *kE)
// {
//     Key *k = (Key *) key;
//     key_enc *ke = (key_enc *) kE;

//     if (compare(add(*k, ke->pSum), ke->encrypted) == 0)
//     {
        
//     }
// }
