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

#include "../include/key.h"

/**
 * Brute force solution
 *
 * input: encrypted key and the T teble.
 * output: possible passwords table.
 * pre condition: none.
 * post condition: table and key unchanged.
 */
Key *brute_force(Key encrypted, Key T[]);
