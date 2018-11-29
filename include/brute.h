/**
 * ED2-2018-2-TC3: Password Cracking problem
 * 
 * Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
 * 
 **********************************************************
 *
 * brute.h: brute force solution inplementations
 */

#ifndef BRUTE_H_

#define BRUTE_H_

#include "../include/key.h"

typedef struct{
    Key value;
    int position;
} Table;

/**
 * Brute force solution
 *
 * input: encrypted key and the T teble.
 * output: possible passwords vector.
 * pre condition: T sorted by values.
 * post condition: vector dynamically allocated, nPass <- number of passwords found.
 */
Key *brute_force(Key encrypted, Table *T, int *nPass);

#endif
