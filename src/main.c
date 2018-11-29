/**
 * ED2-2018-2-TC3: Password Cracking problem
 * 
 * Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
 * 
 **********************************************************
 *
 * main.c: program's entry point
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/key.h"
#include "../include/brute.h"

int comparator(const void *, const void *);

int main(int argc, char *argv[])
{
    Key encrypted;      // encrypted password.
    Table T[N];         // T table.
    Key *passwords;     // possible decrypted passwords vector.
    int nPass = 0;      // number of passwords found.

    if (argc != 2) {
        fprintf(stderr, "Usage: ./decrypt [encrypted] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    encrypted = init_key((unsigned char *) argv[1]);
    // Exibe a senha informada.
    printf("   ");
    print_key(encrypted);
    printf("\n");

    // Reading T table.
    unsigned char buffer[C+1];
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        T[i].value = init_key(buffer);
        T[i].position = i;
    }

    qsort(T, N, sizeof(Table), comparator); // Sorting T by values.

    // for( int i = 0; i < N; i++)
    // {
    //     printf("%d - ", T[i].position);
    //     print_key_char(T[i].value);
    // }

    passwords = brute_force(encrypted, T, &nPass);  // Barbarity.

    for( int i = 0; i < nPass; i++)     // Printing passwords.
    {
        print_key_char(passwords[i]);
    }

    free(passwords);

    return 0;
}

int comparator(const void *a, const void *b)
{
    Key *k = (Key *) a;
    Key *y = (Key *) b;
    return compare(*k, *y);
}
