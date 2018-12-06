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

#define K (N/4)

/**
 * Auxiliar function that convert a binary password (represented in a int vector) to the corresponding key:
 *
 * input: int vector of the binary.
 * output: corresponding key in unsigned chars.
 * pre condition: none.
 * post condition: characters dynamically allocated and must be freed by the client.
 */
unsigned char *convert(int *);

/**
 * Auxiliar function that convert a binary password (represented in int vector and a key) to the corresponding key:
 *
 * input: int vector with the N-K most significant digits and a Key with the K less signifcant digits of the binary.
 * output: corresponding key in unsigned chars.
 * pre condition: none.
 * post condition: characters dynamically allocated and must be freed by the client.
 */
unsigned char *convert_2(int *, Key);

/**
 * Auxiliar function that sum all values in S table to find the decrypted passwords and print them:
 *
 * input: pointers to the encrypted key, to the table S and to a int vector and a key representing the previous sum.
 * output: none.
 * pre condition: binpass with max size of at least N.
 * post condition: encrypted key, S and pSum unchanged.
 */
void find_S(Key *encrypted, STable *S, int binpass[], Key pSum);

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

    build_S(T, S, binpass, init_key(c), N-K, false);
    printf("\n");

    STable_Print(S);

    // find(&encrypted, T, S, binpass, init_key(c), 0, true);

    free(c);
    STable_Destroy(S);
}

// void find(Key *encrypted, Key T[], STable *S, int binpass[], Key pSum, int k, bool change)
// {
//     // Checking previous sum:
//     if (change && compare(pSum, *encrypted) == 0)
//     {
//         unsigned char *c = convert(binpass);
//         printf("%s\n", c);                      // Printing the sum if it matches the encrypted key.
//         free(c);
//     }
//     if (k >= N - K) // Cutoff condition.
//     {
//         find_S(encrypted, S, binpass, pSum);
//         return;
//     }
//     if (k >= N) // Stop condition (for safety).
//     {
//         return;
//     }

//     // Checking all combinations with previous sum, without the current key (change is false because pSum was checked previously).
//     find(encrypted, T, S, binpass, pSum, k + 1, false);

//     Key sum = add(pSum, T[k]);  // Adding current key to the sum.
//     binpass[k] = 1;             // Marking key as added in the binary vector.

//     // Recursively checking all combinations with the new sum:
//     find(encrypted, T, S, binpass, sum, k + 1, true);

//     binpass[k] = 0; // Unchecking the current key to restart it's condition.
// }

// void find_S(Key *encrypted, STable *S, int binpass[], Key pSum)
// {
//     unsigned char tableKey[C];
//     for (int i = 0; i < C-1; i++)
//         tableKey[i] = 'a';

//     tableKey[C-1] = 'b';
//     Key key = init_key(tableKey);
//     Key adder = init_key(tableKey);
//     Key sum;

//     for (int i = 0; i < STable_Size(S); i++)
//     {
//         sum = add(pSum, STable_GetValue(S, key));
//         if (compare(sum, *encrypted) == 0)
//         {
//             unsigned char *c = convert_2(binpass, key);
//             printf("%s\n", c);                      // Printing the sum if it matches the encrypted key.
//             free(c);
//         }
//         key = add(key, adder);
//     }
// }

void build_S(Key T[], STable *S, int binpass[], Key pSum, int k, bool change)
{
    // Adding previous sum, if it changes:
    if (change)
    {
        unsigned char *c = convert(binpass);
        //printf("%s ", c);
        STable_Insert(S, init_key(c), pSum);
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

unsigned char *convert(int *binpass)
{
    int sum = 0;            // Alphabet's character.
    unsigned char *k = malloc((C + 1) * sizeof(unsigned char));     // Characters.

    for(int i = 0, j = 0; i < C; i++)   // Converting each character from binary.
    {
        sum = 0;
        sum += binpass[j++] << 4;
        sum += binpass[j++] << 3;
        sum += binpass[j++] << 2;
        sum += binpass[j++] << 1;
        sum += binpass[j++];

        k[i] = ALPHABET[sum];       // Finding the corresponding caracter in the alphabet.
    }

    return k;
}

unsigned char *convert_2(int *binpass, Key key)
{
    int i, j, sum = 0;            // Alphabet's character.
    unsigned char *k = malloc((C + 1) * sizeof(unsigned char));     // Characters.

    for(i = 0, j = 0; i < C - K/B; i++)   // Converting the first C - K/B characters from binary.
    {
        sum = 0;
        sum += binpass[j++] << 4;
        sum += binpass[j++] << 3;
        sum += binpass[j++] << 2;
        sum += binpass[j++] << 1;
        sum += binpass[j++];

        k[i] = ALPHABET[sum];       // Finding the corresponding caracter in the alphabet.
    }
    while (i < C)                   // Getting the last K/B characters from key.
    {
        sum = 0;
        sum += bit(key, j++) << 4;
        sum += bit(key, j++) << 3;
        sum += bit(key, j++) << 2;
        sum += bit(key, j++) << 1;
        sum += bit(key, j++);

        k[i++] = ALPHABET[sum];
    }

    return k;
}
