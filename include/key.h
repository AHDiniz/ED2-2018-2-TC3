#ifndef KEY_H
#define KEY_H

#define C 8          // Password's character number
#define B 5          // Character's bit number
#define R (1 << B)   // Alphabet size
#define N (B * C)    // Number of bits by password

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"

long long int mem=0;

// An integer module R made by C digits. The array is inside
// a struct to ease memory manegement and
// the attribute passing in functions
typedef struct {
    unsigned char digit[C];
} Key;

// Initializes and returns a key from the given char array
// Example: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[]);

// Prints the given key in stdout in three formats: chars, ints (base R) and binary
void print_key(Key k);

// Prints the given key in stdout in the char format
void print_key_char(Key k);

// Returns the i-th bit from the given key
int bit(Key k, int i);

// Returns a + b (mod 2^N) .
Key add(Key a, Key b);

// Adds (module 2^N) and returns the subset of integers T[i] that
// are indexed by the bits of k
Key subset_sum(Key k, Key T[N]);

int compare(Key k, Key y);

Key sub(Key a, Key b);

#endif
