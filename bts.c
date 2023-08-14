#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char * data; // Pointer to the linked list node
    struct TreeNode* left;
    struct TreeNode* right;
} Tree_node;

Tree_node * insert(Tree_node *root, char *value)
{
    if (!root)
    {
        Tree_node * newNode = (Tree_node *)malloc(sizeof(Tree_node));
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    int compareResult = strcmp(value, root->data);
    if (compareResult < 0)
    {
        root->left = insert(root->left, value);
    }
    else if (compareResult > 0)
    {
        root->right = insert(root->right, value);
    }
    return root;
}

void inOrderTraversal(Tree_node *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        printf("%s\n", root->data);
        inOrderTraversal(root->right);
    } 
}

int main (int argc, char **argv)
{
    Tree_node *root;

    root = insert(root, argv[1]);
    root = insert(root, argv[2]);
    root = insert(root, argv[3]);
    root = insert(root, argv[4]);

    inOrderTraversal(root);

}