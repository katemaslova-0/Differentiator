#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "TreeFunc.h"
#include "GraphDump.h"
#include "GetFunc.h"
#include "ReadFunc.h"

Err_t TreeCtor (Tree_t * tree, FILE * log) // ?
{
    assert(tree);
    assert(log);

    tree->root = (Node_t *) calloc (1, sizeof(Node_t));
    if (!tree->root)
        return kMemAllocError;

    SetRoot(tree);

    tree->size = 1;
    tree->log = log;

    return kNoError;
}


void SetRoot (Tree_t * tree) // ?
{
    assert(tree);
    assert(tree->root);

    (tree->root)->left   = NULL;
    (tree->root)->right  = NULL;
    (tree->root)->parent = NULL;
}


Err_t NodeVerify (Node_t * node, Tree_t * tree, int count = 0)
{
    assert(tree);

    Err_t error = kNoError;

    if (count > tree->size)                              {error = kRecursiveOverflow; return error;}
    if (node == NULL)                                    {error = kNullNodePointer;   return error;}
    if (node == node->left || node == node->right)       {error = kTwoDads;           return error;}
    if (node->right == node->left && node->left != NULL) {error = kSimilarChildren;   return error;}
    if (node->right && (node->right)->parent != node)    {error = kWrongRightChild;   return error;}
    if (node->left  && (node->left)->parent  != node)    {error = kWrongLeftChild;    return error;}

    if (!node->left) NodeVerify(node->left, tree, ++count);
    if (!node->right) NodeVerify(node->right, tree, ++count);

    return error;
}


void OutputNode (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, "f%p [shape=Mrecord; style = filled; fillcolor = "light_pink"; ", node);
    fprintf(fp, "color = "dark_green"; label = \"{parent = %p | address = %p ", node->parent, node);

    fprintf(fp, "| type = %s ", GetNodeType(node->type)); //FIXME: check return value
    switch(node->type)
    {
        case Num_t: fprintf(fp, "| value = %f ", (node->value).num);               break;
        case Var_t: fprintf(fp, "| value = %f (%c)", (node->value).var.value, (node->value).var.name); break;
        case Op_t:  fprintf(fp, "| value = %s ", GetOperation((node->value).cmd)); break; //FIXME: check return value
        default:    fprintf(fp, "| NODE TYPE ERROR ");                       break;
    }
    fprintf(fp, "| {left = %p | right = %p}} \"]; \n", node->left, node->right);

    if (node->left)
    {
        OutputNode(fp, node->left);
        fprintf(fp, "f%p -> f%p [color = "dark_pink"];\n", node, node->left);
    }
    if (node->right)
    {
        OutputNode(fp, node->right);
        fprintf(fp, "f%p -> f%p [color = "dark_pink"];\n", node, node->right);
    }
}


void NodeDtor (Node_t * node)
{
    assert(node);

    if (node->left)
        NodeDtor(node->left);
    if (node->right)
        NodeDtor(node->right);

    free(node);
}


/*void VarNamesDtor (Node_t * node)
{
    assert(node);

    if (node->left)
        VarNamesDtor(node->left);
    if (node->right)
        VarNamesDtor(node->right);

    if (node->type == Var_t)
        free(node->value.var.name);
}*/


