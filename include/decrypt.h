/**********************************************************
 * ED2-2018-2-TC3: Password Cracking problem
 * 
 * Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
 * 
 *
 * decrypt.h: decrypt definitions
 **********************************************************/

#ifndef DECRYPT_H_

#define DECRYPT_H_

#include "key.h"

/**
 * Decrypt function
 *
 * input: encrypted key and the T teble.
 * output: none.
 * pre condition: none.
 * post condition: none.
 */
void decrypt(Key encrypted, Key *T);

#endif
