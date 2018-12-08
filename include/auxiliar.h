/**********************************************************
 * ED2-2018-2-TC3: Password Cracking problem
 * 
 * Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
 * 
 *
 * auxiliar.h: commun used auxiliar functions implementations
 **********************************************************/

#ifndef AUXILIAR_H_

#define AUXILIAR_H_

#include "key.h"

#define K ( N > 25 ? 25 : (N/2))

/**
 * Auxiliar function that convert a binary password (represented in a int vector) to the corresponding key:
 *
 * input: int vector of the binary.
 * output: corresponding key in unsigned chars.
 * pre condition: none.
 * post condition: characters dynamically allocated and must be freed by the client.
 */
unsigned char *convert(int *binpass);

/**
 * Auxiliar function that convert a binary password (represented in int vector and a key) to the corresponding key:
 *
 * input: int vector with the N-K most significant digits and a Key with the K less signifcant digits of the binary.
 * output: corresponding key in unsigned chars.
 * pre condition: none.
 * post condition: characters dynamically allocated and must be freed by the client.
 */
unsigned char *convert_2(int *binpass, Key key);

#endif
