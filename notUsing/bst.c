#include <stdio.h>
#include <stdlib.h>

#include "../include/bst.h"

struct bst
{
    Key key;
    struct bst* left;
    struct bst* right;
};

BST* BST_Create(Key key)
{
    BST* tree = (BST *) malloc(sizeof(BST));
    tree->key = key;
    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

int BST_Empty(BST* root)
{
    return root == NULL;
}

BST* BST_Insert(BST* root, BST* node)
{
    if(root != NULL)
    {
        if(compare(node->key, root->key) == 0)
        {
            BST_Destroy(node);
            return root;
        }
        if(compare(node->key, root->key) < 0)
            root->left = BST_Insert(root->left,node);
        else
            root->right = BST_Insert(root->right,node);
    }
    else return node;
    return root;
}

int BST_Altura(BST* root)
{
    if(root == NULL)
        return -1;
    int aEsq = 1 + BST_Altura(root->left);
    int aDir = 1 + BST_Altura(root->right);

    return (aEsq > aDir) ? aEsq : aDir;
}

void BST_Destroy(BST* root)
{
    if(root != NULL)
    {
        BST_Destroy(root->left);
        BST_Destroy(root->right);
        free(root);
    }
}

void BST_Print(BST* root)
{
    printf("<");
    if(root != NULL)
    {
        BST_Print(root->left);
        print_key_char(root->key);
        BST_Print(root->right);
    }
    printf(">");
}