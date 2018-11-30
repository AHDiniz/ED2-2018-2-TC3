/**
 * ED2-2018-2-TC3: Password Cracking problem
 * 
 * Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
 * 
 **********************************************************
 *
 * brute.c: brute force solution definitions
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/brute.h"

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
 * Auxiliar recursive function that sum all possible combinations of T table's keys to find the decrypted passwords and print them:
 *
 * input: pointers to the encrypted key, to the table T and to a int vector, a key representing the previous sum, a int representing the current position of T being used and a bool that informs if the key was already cheked.
 * output: none.
 * pre condition: T sorted, binpass with max size of at least N.
 * post condition: encrypted key and T unchanged.
 * 
 */
void force(Key *encrypted, Key T[], int binpass[], Key pSum, int k, bool change);

void brute_force(Key encrypted, Key *T)
{
    int binpass[N] = { 0 };                     // Binary password.
    unsigned char *c = convert(binpass);        // Initial key. (all bits = 0)

    force(&encrypted, T, binpass, init_key(c), 0, true);

    free(c);
}

unsigned char *convert(int *binpass)
{
    int sum = 0;            // Alphabet's character.
    unsigned char *k = malloc((C + 1) * sizeof(unsigned char));     // Characters.

    for(int i = 0, j = 0; i < C; i++)   // Converting each character from binary.
    {
        sum = 0;
        sum += binpass[j++] * 16;
        sum += binpass[j++] * 8;
        sum += binpass[j++] * 4;
        sum += binpass[j++] * 2;
        sum += binpass[j++];

        k[i] = ALPHABET[sum];       // Finding the corresponding caracter in the alphabet.
    }

    return k;
}

void force(Key *encrypted, Key T[], int binpass[], Key pSum, int k, bool change)
{
    // Checking previous sum:
    if (change && compare(pSum, *encrypted) == 0)
    {
        unsigned char *c = convert(binpass);
        printf("%s\n", c);                      // Printing the sum if it matches the encrypted key.
        free(c);
    }
    if (k >= N) // Stop condition.
    {
        return;
    }

    Key sum = add(pSum, T[k]);  // Adding current key to the sum.
    binpass[k] = 1;             // Marking key as added in the binary vector.

    // Recursively checking all combinations with the new sum:
    force(encrypted, T, binpass, sum, k + 1, true);

    binpass[k] = 0; // Unchecking the current key to check all combinations without it.

    // Checking all combinations with pSum, without the current key (change is false because pSum was checked previously).
    force(encrypted, T, binpass, pSum, k + 1, false);
}
