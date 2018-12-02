#include "../include/symbolTable.h"
#include <stdlib.h>

typedef struct node Node;
struct node
{
    Key key;
    Node *right, *left;
};

static Node *Node_Create(Key key)
{
    Node *node = malloc(sizeof(*node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

static Node *Node_Destroy(Node *node)
{
    if (node == NULL) return NULL;
    node->left = Node_Destroy(node->left);
    node->right = Node_Destroy(node->right);
    free(node);
    return NULL;
}

static Node *Node_Insert(Node *root, Key key)
{
    if (root == NULL) return Node_Create(key);
    if (compare(key, root->key) < 0) root->left = Node_Insert(root->left, key);
    else root->right = Node_Insert(root->right, key);
    return root;
}

static int Node_Leaf(Node *node)
{
    return node->left == NULL && node->right == NULL;
}

static Node *Node_Delete(Node *root, Key key)
{
    if (compare(key, root->key) < 0) root->left = Node_Delete(root->left, key);
    else if (compare(key, root->key) < 0) root->right = Node_Delete(root->right, key);
    else
    {
        if (Node_Leaf(root))
        {
            free(root);
            root = NULL;
        }
        else if (root->left == NULL)
        {
            Node *target = root;
            root = root->right;
            free(root);
        }
        else if (root->right == NULL)
        {
            Node *target = root;
            root = root->left;
            free(root);
        }
        else
        {
            Node *newTarget = root->left;
            while (newTarget != NULL) newTarget = newTarget->right;

            root->key = newTarget->key;
            newTarget->key = key;

            root->left = Node_Delete(root->left, key);
        }
    }
    return root;
}

struct sTable
{
    Node *root;
    int size;
};

STable *STable_Create(int max)
{
    STable *table = malloc(sizeof(*table));
    table->size = 0;
    table->root = NULL;
    return table;
}

void STable_Destroy(STable *table)
{
    if (table == NULL) return;
    table->root = Node_Destroy(table->root);
    free(table);
}

int STable_Empty(STable *table)
{
    return table == NULL || table->root = NULL;
}

int STable_Size(STable *table)
{
    return table->size;
}

void STable_Insert(STable *table, Key key)
{
    table->root = Node_Insert(table->root, key);
    table->size++;
}

int STable_Contains(STable *table, Key key)
{
    if (STable_Empty(table)) return 0;
    Node *target;
    for (target = table->root; target != NULL && compare(key, target->key) != 0; target = (compare(key, target->key) < 0) ? target->left : tagert->right);
    return target != NULL;
}

void STable_Delete(STable *table, Key key)
{
    if (STable_Empty(table)) return;
    table->root = Node_Delete(table->root, key);
    table->size--;
}
