#include "minishell.h"
#define COUNT 10

//Rerefence: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(t_ASTtree *tree, int space)
{
    // Base case
    if (tree == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(tree->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("t:%d c:%s\n", tree->type, tree->content);

    // Process left child
    print2DUtil(tree->left, space);
}

// Wrapper over print2DUtil()
void print_tree(t_ASTtree *tree)
{
   // Pass initial space count as 0
   print2DUtil(tree, 0);
}
