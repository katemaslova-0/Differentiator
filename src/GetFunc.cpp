#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>

#include "Data.h"
#include "GetFunc.h"

const int SIZE_OF_PIC_NAME = 80;
const int SIZE_OF_COMMAND = 80;

const char * GetPlace (Place_t place)
{
    if (place == Before)
        return "BEFORE";
    else if (place == After)
        return "AFTER"; // FIXME: fix return
    else
        return "AT";
}


char * GetCommand (char * pic_name)
{
    assert(pic_name);

    char * command = (char *) calloc (SIZE_OF_COMMAND, sizeof(char));
    if(!command) return NULL;

    sprintf(command, "dot diffdump.txt -T png -o %s", pic_name);

    return command;
}


char * GetPicName (void)
{
    static int pic_count = 0;

    char * pic_name = (char *) calloc (SIZE_OF_PIC_NAME, sizeof(char));
    if(!pic_name) return NULL;

    sprintf(pic_name, "diffdump%d.png", pic_count);
    pic_count++;

    return pic_name;
}


const char * GetOperation (Calc_t operation)
{
    switch(operation)
    {
        case AddCmd:    return "ADD";    break;
        case MulCmd:    return "MUL";    break;
        case SinCmd:    return "SIN";    break;
        case DivCmd:    return "DIV";    break;
        case CosCmd:    return "COS";    break;
        case TanCmd:    return "TAN";    break;
        case CtgCmd:    return "CTG";    break;
        case PowCmd:    return "POW";    break;
        case ArcsinCmd: return "ARCSIN"; break;
        case ArccosCmd: return "ARCCOS"; break;
        case ArctgCmd:  return "ARCTG";  break;
        case ArcctgCmd: return "ARCCTG"; break;
        case LnCmd:     return "LN";     break;
        case LogCmd:    return "LOG";    break;
        default:        return  NULL;
    }
}


const char * GetNodeType (int type)
{
    switch(type)
    {
        case Num_t: return "NUM"; break;
        case Var_t: return "VAR"; break;
        case Op_t:  return "OP";  break;
        default:    return  NULL;
    }
}


FILE * GetLog (Tree_t * tree)
{
    assert(tree);

    return tree->log;
}


int GetFileSize (const char * filename)
{
    assert(filename);

    struct stat st;
    stat(filename, &st);

    return (int)st.st_size;
}
