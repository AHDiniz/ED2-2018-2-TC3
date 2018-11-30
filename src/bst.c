#include <stdio.h>
#include <stdlib.h>

#include "../include/bst.h"

struct bst {
    Key chave;
    struct bst* esq;
    struct bst* dir;
};

BST* BST_CriaVazia() {
    return NULL;
}

BST* BST_CriaNo(Key chave) {
    BST* arv = malloc(sizeof(BST));
    arv->chave = chave;
    arv->esq = BST_CriaVazia();
    arv->dir = BST_CriaVazia();

    return arv;
}

int BST_Vazia(BST* raiz) {
    if(raiz == NULL) {
        return 1;
    }
    return 0;
}

BST* BST_AddNo(BST* raiz, BST* no) {
    if(raiz != NULL) {
        if(compare(no->chave, raiz->chave) == 0) {
            BST_Destroi(no);
            return raiz;
        }
        if(compare(no->chave, raiz->chave) < 0) {
            raiz->esq = BST_AddNo(raiz->esq,no);
        }
        else {
            raiz->dir = BST_AddNo(raiz->dir,no);
        }
    }
    else {
        return no;
    }
    return raiz;
}

//BST* BST_RemoveNo(BST* raiz, int chave);

int BST_Altura(BST* raiz) {
    if(raiz == NULL) {
        return -1;
    }
    int aEsq = 1 + BST_Altura(raiz->esq);
    int aDir = 1 + BST_Altura(raiz->dir);

    return (aEsq > aDir) ? aEsq : aDir;
}

void BST_Destroi(BST* raiz) {
    if(raiz != NULL) {
        BST_Destroi(raiz->esq);
        BST_Destroi(raiz->dir);
        free(raiz);
    }
}

void BST_Imprime(BST* raiz) {
    printf("<");
    if(raiz != NULL) {
        BST_Imprime(raiz->esq);
        print_key_char(raiz->chave);
        BST_Imprime(raiz->dir);
    }
    printf(">");
}