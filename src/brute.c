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

#include "../include/brute.h"

/**
 * Auxiliar function that convert a binary password (represented in a int vector) to the corresponding key:
 *
 * input: int vector of binary.
 * output: corresponding key.
 * pre condition: 
 * post condition: 
 */
Key convert(int *);

/**
 * Auxiliar recursive function that sum all possible combinations and find the decrypted passwords:
 *
 * input: pointers to the encrypted key, Table T
 * output: none.
 * pre condition: 
 * post condition: 
 */
void force(Key *encrypted, Table *T, int *nPass, Key *passwords, int *binpass);

Key *brute_force(Key encrypted, Table *T, int *nPass)
{
    int binpass[N] = { 0 };                     // Binary password.
    Key *passwords = malloc(40 * sizeof(Key));  // Passwords found.

    // Testing:
    passwords[0] = convert(binpass);
    *nPass += 2;

    for (int i = 0; i < N; i++)
    {
        if (bit(encrypted, i))
            binpass[i] = 1;
    }
    passwords[1] = convert(binpass);

    return passwords;
}

Key convert(int *binpass)
{
    int sum = 0;            // Alphabet's character.
    unsigned char k[C];     // Key's characters.

    for(int i = 0, j = 0; i < C; i++)   // Converting each character from binary.
    {
        sum = 0;
        sum += binpass[j++] * 16;
        sum += binpass[j++] * 8;
        sum += binpass[j++] * 4;
        sum += binpass[j++] * 2;
        sum += binpass[j++];

        k[i] = ALPHABET[sum];
    }

    return init_key(k);
}
