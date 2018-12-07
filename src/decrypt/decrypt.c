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

#define K (N/2)

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
    int binpass[N] = { 0 };                             // Binary password.
    unsigned char *c = convert(binpass);              // Initial key. (all bits = 0)

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
        // find_S(encrypted, S, binpass, pSum);
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

void find_S(Key *encrypted, STable *S, int binpass[], Key pSum)
{
    Key subt = sub(*encrypted, pSum);

    STable_PrintKey(S, subt, binpass);

    // Key sum;

    // for (int i = 1; i < STable_Size(S); i++)
    // {
    //     sum = add(pSum, STable_GetValue(S, i));
    //     if (compare(sum, *encrypted) == 0)
    //     {
    //         unsigned char *c = convert_2(binpass, i);
    //         printf("%s\n", c);                      // Printing the sum if it matches the encrypted key.
    //         free(c);
    //     }
    // }
}

void build_S(Key T[], STable *S, int binpass[], Key pSum, int k, bool change)
{
    // Adding previous sum, if it changes:
    if (change)
    {
        // int j = 0;
        // for(int i = 0; i < K; i++)
        // {
        //     j += binpass[N-1-i] << i;
        // }
        // STable_Insert(S, j, pSum);
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

unsigned char *convert(int *binpass)
{
    int sum;                                                        // Auxiliar variables.
    unsigned char *key = malloc((C + 1) * sizeof(unsigned char));     // Characters.

    for(int i = 0, j = 0; i < C; i++)   // Converting each character from binary.
    {
        sum = 0;
        sum += binpass[j++] << 4;
        sum += binpass[j++] << 3;
        sum += binpass[j++] << 2;
        sum += binpass[j++] << 1;
        sum += binpass[j++];

        key[i] = ALPHABET[sum];       // Finding the corresponding caracter in the alphabet.
    }

    return key;
}

unsigned char *convert_2(int *binpass, Key key) // int n)
{
    int i, j, sum;                                                  // Auxiliar variables.
    // char bin[K];
    unsigned char *k = malloc((C + 1) * sizeof(unsigned char));     // Characters.

    i = j = sum = 0;

    for(i = 0, j = 0; i < N - K; i++)   // Converting the first N-k bits of the string from binary.
    {
        switch (i % 5)
        {
            case 0: sum = 0;
                    sum += binpass[i] << 4;
                    break;
            case 1: sum += binpass[i] << 3;
                    break;
            case 2: sum += binpass[i] << 2;
                    break;
            case 3: sum += binpass[i] << 1;
                    break;
            case 4: sum += binpass[i];
                    k[j++] = ALPHABET[sum]; // Finding the corresponding caracter in the alphabet.
        }
    }

    // for (k = K-1; k >= 0; k--)
    // {
    //     if (n % 2 == 0)
    //     {
    //         bin[k] = 0;
    //         n = n / 2;
    //     }
    //     else
    //     {
    //         bin[k] = 1;
    //         n = n / 2;
    //     }
    // }

    // for (k = 0; i < N; k++)                           // Getting the last K bits from key.
    // {
    //     switch (i % 5)
    //     {
    //         case 0: sum = 0;
    //                 sum += bin[k] << 4;
    //                 i++;
    //                 break;
    //         case 1: sum += bin[k] << 3;
    //                 i++;
    //                 break;
    //         case 2: sum += bin[k] << 2;
    //                 i++;
    //                 break;
    //         case 3: sum += bin[k] << 1;
    //                 i++;
    //                 break;
    //         case 4: sum += bin[k];
    //                 key[j++] = ALPHABET[sum];
    //                 i++;
    //     }
    // }
    
    while (i < N)                           // Getting the last K bits from key.
    {
        switch (i % 5)
        {
            case 0: sum = 0;
                    sum += bit(key, i++) << 4;
                    break;
            case 1: sum += bit(key, i++) << 3;
                    break;
            case 2: sum += bit(key, i++) << 2;
                    break;
            case 3: sum += bit(key, i++) << 1;
                    break;
            case 4: sum += bit(key, i++);
                    k[j++] = ALPHABET[sum];
        }
    }

    return k;
}
