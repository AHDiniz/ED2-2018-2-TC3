/**********************************************************
 * ED2-2018-2-TC3: Password Cracking problem
 * 
 * Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
 * 
 *
 * auxiliar.c: commun used auxiliar functions definitions
 **********************************************************/

#include "../include/auxiliar.h"

// Auxiliar function that convert a binary password (represented in a int vector) to the corresponding key:
unsigned char *convert(int *binpass)
{
    int sum = 0;                                                    // Auxiliar variables.
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


// Auxiliar function that convert a binary password (represented in int vector and a key) to the corresponding key:
unsigned char *convert_2(int *binpass, Key key)
{
    int i, j, sum;                                                  // Auxiliar variables.
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
