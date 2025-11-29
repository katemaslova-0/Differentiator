#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "Data.h"
#include "DiffFunc.h"
#include "ReadFunc.h"
#include "TreeFunc.h"
#include "LatexDump.h"

#define RETURN_IF_NOT_ALLOCATED(node) if (!node) {printf("Memory allocation error\n"); return NULL;}

#define dR Differentiate(fp, tree, node->right)
#define dL Differentiate(fp, tree, node->left)
#define cR CopyNode(node->right)
#define cL CopyNode(node->left)

#define ADD_(node1, node2) MakeNewNode(Op_t, {.cmd = AddCmd}, node1, node2)
#define MUL_(node1, node2) MakeNewNode(Op_t, {.cmd = MulCmd}, node1, node2)
#define DIV_(node1, node2) MakeNewNode(Op_t, {.cmd = DivCmd}, node1, node2)
#define POW_(node1, node2) MakeNewNode(Op_t, {.cmd = PowCmd}, node1, node2)
#define SIN_(node)         MakeNewNode(Op_t, {.cmd = SinCmd}, NULL, node)
#define COS_(node)         MakeNewNode(Op_t, {.cmd = CosCmd}, NULL, node)
#define TAN_(node)         MakeNewNode(Op_t, {.cmd = TanCmd}, NULL, node)
#define LN_(node)          MakeNewNode(Op_t, {.cmd = LnCmd},  NULL, node)
#define NUM_(value)        MakeNewNode(Num_t, {.num = value}, NULL, NULL)


Node_t * Differentiate (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(tree);
    assert(node);

    switch(node->type)
    {
        case Num_t: return DiffNum(fp, tree, node); break;
        case Var_t: {if (node->value.var.name == 'x') // FIXME
                        return DiffVar(fp, tree, node);
                    else
                        return DiffNum(fp, tree, node);
                    break;}
        case Op_t:
        {
            switch((node->value).cmd)
            {
                case AddCmd:    return DiffAdd(fp, tree, node);    break;
                case MulCmd:    return DiffMul(fp, tree, node);    break;
                case DivCmd:    return DiffDiv(fp, tree, node);    break;
                case SinCmd:    return DiffSin(fp, tree, node);    break;
                case CosCmd:    return DiffCos(fp, tree, node);    break;
                case TanCmd:    return DiffTan(fp, tree, node);    break;
                case CtgCmd:    return DiffCtg(fp, tree, node);    break;
                case PowCmd:    return DiffPow(fp, tree, node);    break;
                case ArcsinCmd: return DiffArcsin(fp, tree, node); break;
                case ArccosCmd: return DiffArccos(fp, tree, node); break;
                case ArctgCmd:  return DiffArctg(fp, tree, node);  break;
                case ArcctgCmd: return DiffArcctg(fp, tree, node); break;
                case LogCmd:    return DiffLog(fp, tree, node);    break;
                case LnCmd:     return DiffLn(fp, tree, node);     break;
                default:        printf("%s: Command is not found\n", __FUNCTION__);
            }
            break;
        }
        default: printf("%s: Type is not found\n", __FUNCTION__);
    }

    return NULL;
}


Node_t * CopyNode (Node_t * node)
{
    assert(node);

    Node_t * new_node = AllocateNodeMemory();
    RETURN_IF_NOT_ALLOCATED(new_node);

    new_node->value = node->value;
    new_node->type = node->type;

    if (node->left)
        new_node->left = CopyNode(node->left);
    else
        new_node->left = NULL;

    if (node->right)
        new_node->right = CopyNode(node->right);
    else
        new_node->right = NULL;

    return new_node;
}


Node_t * MakeNewNode (Type_t type, Value_t value, Node_t * left, Node_t * right)
{
    Node_t * node = AllocateNodeMemory();
    RETURN_IF_NOT_ALLOCATED(node);

    node->value = value;
    node->type  = type;

    node->left  = left;
    node->right = right;

    return node;
}


Node_t * DiffNum (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = NUM_(0);

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffVar (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = NUM_(1);

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffAdd (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = ADD_(dL, dR);

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffMul (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = ADD_(MUL_(dL, cR), MUL_(cL, dR));

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffDiv (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = DIV_(ADD_(MUL_(dL, cR), MUL_(MUL_(cL, dR), NUM_(-1))), MUL_(cR, cR));

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffSin (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(COS_(cR), dR);

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffCos (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(MUL_(SIN_(cR), NUM_(-1)), dR);

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n"); //

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffTan (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(DIV_(NUM_(1), MUL_(COS_(cR), COS_(cR))), dR);

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffCtg (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(DIV_(NUM_(-1), MUL_(SIN_(cR), SIN_(cR))), dR);

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffPow (FILE * fp, Tree_t * tree, Node_t * node) // check!
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = NULL;

    if (node->right->type == Num_t)
        res = MUL_(cR, MUL_(dL, POW_(cL, ADD_(cR, NUM_(-1)))));
    else if (node->left->type == Num_t && node->right->type != Num_t)
        res = MUL_(POW_(cL, cR), MUL_(LN_(cL), dR));
    else if (node->left->type != Num_t && node->right->type != Num_t)
        res = MUL_(POW_(NUM_(exp(1)), MUL_(LN_(cL), cR)), ADD_(MUL_(dR, LN_(cL)), DIV_(MUL_(dL, cR), cL)));
    else
        printf("%s:%d: ERROR\n", __FUNCTION__, __LINE__);

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffArcsin (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(dR, DIV_(NUM_(1), POW_(ADD_(NUM_(1), MUL_(MUL_(cR, cR), NUM_(-1))), NUM_(0.5))));

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffArccos (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(dR, DIV_(NUM_(-1), POW_(ADD_(NUM_(1), MUL_(MUL_(cR, cR), NUM_(-1))), NUM_(0.5))));

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffArctg (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(dR, DIV_(NUM_(1), ADD_(NUM_(1), MUL_(cR, cR))));

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffArcctg (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(dR, DIV_(NUM_(-1), ADD_(NUM_(1), MUL_(cR, cR))));

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffLog (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(dR, DIV_(NUM_(1), MUL_(cR, LN_(cL))));

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}


Node_t * DiffLn (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(fp);
    assert(node);
    assert(tree);

    Node_t * res = MUL_(dR, DIV_(NUM_(1), cR));

    OutputPhrase(fp);

    fprintf(fp, "\\begin{center}\n");

    DumpNodeBeforeDiff(fp, tree, node);

    fprintf(fp, " = ");

    DumpNodeToLatex(fp, res);

    fprintf(fp, "\\] \\end{center}\n");

    return res;
}
