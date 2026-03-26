#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "Data.h"
#include "Calculate.h"
#include "GraphDump.h"
#include "TreeFunc.h"


double Calculate (Tree_t * tree, Node_t * node) // FIXME: is it possible to make it smaller?
{
    assert(tree);
    assert(node);

    switch(node->type)
    {
        case Num_t: return (node->value).num;       break;
        case Var_t: return (node->value).var.value; break;
        case Op_t:
        {
            switch((node->value).cmd)
            {
                case AddCmd:    return Calculate(tree, node->left) + Calculate(tree, node->right);
                                break;

                case MulCmd:    return Calculate(tree, node->left) * Calculate(tree, node->right);
                                break;

                case DivCmd:    return Calculate(tree, node->left) / Calculate(tree, node->right);
                                break;

                case SinCmd:    return sin(Calculate(tree, node->right));
                                break;

                case CosCmd:    return cos(Calculate(tree, node->right));
                                break;

                case TanCmd:    return tan(Calculate(tree, node->right));
                                break;

                case CtgCmd:    return 1 / (Calculate(tree, node->right));
                                break;

                case PowCmd:    return pow(Calculate(tree, node->left), Calculate(tree, node->right));
                                break;

                case ArcsinCmd: return asin(Calculate(tree, node->right));
                                break;

                case ArctgCmd:  return atan(Calculate(tree, node->right));
                                break;

                case ArcctgCmd: return atan(1 / Calculate(tree, node->right));
                                break;

                case ArccosCmd: return acos(Calculate(tree, node->right));
                                break;

                case LnCmd:     return log(Calculate(tree, node->right));
                                break;

                case LogCmd:    return log(Calculate(tree, node->right)) / log(Calculate(tree, node->left));
                                break;

                default: printf("%s: Command is not found\n", __FUNCTION__);
            }
            break;
        }
        default:    printf("%s: Type is not found\n", __FUNCTION__);
    }

    return 0; // FIXME: error return value?
}


void OutputResult (double res)
{
    printf("Result: %f\n", res);
}
