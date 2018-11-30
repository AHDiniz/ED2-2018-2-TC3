#ifndef BST_H_

#define BST_H_

#include "key.h"

typedef struct bst BST;

BST* BST_CriaVazia();

BST* BST_CriaNo(Key chave);

int BST_Vazia(BST* raiz);

BST* BST_AddNo(BST* raiz, BST* no);

int BST_Altura(BST* raiz);

void BST_Destroi(BST* raiz);

void BST_Imprime(BST* raiz);

#endif
