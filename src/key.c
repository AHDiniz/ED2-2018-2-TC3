#include <stdio.h>
#include "key.h"

// Initializes and returns a key from the given char array
// Example: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[])
{
    // Converts each char in an int on the interval 0-31.
    Key k;
    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < R; j++)
        {
            if (s[i] == ALPHABET[j])
            {
                k.digit[i] = j;
            }
        }
    }
    // Note que não há problema de retornar uma variável local aqui porque
    // a semântica do C para variáveis do tipo struct (não struct*) é fazer
    // uma cópia da struct inteira. Isso pode parecer ineficiente mas lembre
    // que o vetor da struct de chave é muito pequeno.
    return k;
}

// Prints the given key in stdout in three formats: chars, ints (base R) and binary
void print_key(Key k)
{
    for (int i = 0; i < C; i++)
    {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("  ");
    for (int i = 0; i < C; i++)
    {
        printf("%2d ", k.digit[i]);
    }
    printf("  ");
    for (int i = 0; i < N; i++)
    {
        printf("%d", bit(k, i));
    }
    printf("\n");
}

// Prints the given key in stdout in the char format
void print_key_char(Key k)
{
    for (int i = 0; i < C; i++)
    {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("\n");
}

// Returns the i-th bit from the given key
int bit(Key k, int i)
{
    return (k.digit[i/B] >> (B - 1 - i % B)) & 1;
}

// Returns a + b (mod 2^N) .
Key add(Key a, Key b)
{
    Key c = {{0}};
    int carry = 0;
    for (int i = C-1; i >= 0; i--) {
        int sum = a.digit[i] + b.digit[i] + carry;
        c.digit[i] = sum  % R;
        carry      = sum >= R;
    }
    return c;
}

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N]) {
    Key sum = {{0}};
    for (int i = 0; i < N; i++) {
        if (bit(k, i)) {
            sum = add(sum, T[i]);
            printf("%2d ", i);           // Para teste.
            print_key(T[i]);             // Para teste.
        }
    }
   return sum;
}
