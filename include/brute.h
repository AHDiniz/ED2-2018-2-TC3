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

/**
 * Brute force solution
 *
 * input: encrypted key and the T teble.
 * output: none.
 * pre condition: none.
 * post condition: none.
 */
void brute_force(Key encrypted, Key *T);

#endif
