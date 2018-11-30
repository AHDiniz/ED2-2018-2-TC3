#ifndef BST_H_

#define BST_H_

#include "key.h"

typedef struct bst BST;

BST* BST_Create(Key key);

int BST_Empty(BST* root);

BST* BST_Insert(BST* root, BST* node);

int BST_Height(BST* root);

void BST_Destroy(BST* root);

void BST_Print(BST* root);

#endif
