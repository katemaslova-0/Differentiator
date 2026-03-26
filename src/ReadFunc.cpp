#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "Data.h"
#include "GetFunc.h"
#include "TreeFunc.h"
#include "ReadFunc.h"

const int LENTH_OF_SIN_WORD = 3;
const int LENTH_OF_COS_WORD = 3;
const int LENTH_OF_TAN_WORD = 3;
const int LENTH_OF_CTG_WORD = 3;
const int LENTH_OF_ARCSIN_WORD = 6;
const int LENTH_OF_ARCCOS_WORD = 6;
const int LENTH_OF_ARCCTG_WORD = 6;
const int LENTH_OF_ARCTAN_WORD = 5;
const int LENTH_OF_LOG_WORD = 3;
const int LENTH_OF_LN_WORD = 2;

#define CALL_DUMP  OutputBuf(fp, pos, buffer, tree); \
                   if (node->left && node->right) \
                   {GraphDump(tree, node, NoArg, __FUNCTION__, __FILE__, __LINE__, NULL, NULL, SUCCESS);} \
                   else \
                   { \
                        switch(node->type) \
                        { \
                            case Num_t: {fprintf (fp, "Node 0x%p { value = \"%f\", left = 0x%p, right = 0x%p } -- graph dump skipped\n", \
                            node, (node->value).num, node->left, node->right); break;} \
                            case Var_t: {fprintf (fp, "Node 0x%p { value = \"%f\"(%s), left = 0x%p, right = 0x%p } -- graph dump skipped\n", \
                            node, (node->value).var.value, (node->value).var.name, node->left, node->right); break;} \
                            case Op_t: {fprintf (fp, "Node 0x%p { value = \"%s\", left = 0x%p, right = 0x%p } -- graph dump skipped\n", \
                            node, GetOperation((node->value).cmd), node->left, node->right); break;} \
                            default: fprintf(fp, "NODE ERROR"); \
                        } \
                   }

#define ERROR_IN_TREE_CODE(fp, sym)  fprintf(fp, "<font color = red> ERROR in tree code: POS = [%c]\n <font color = black>", sym)

/*Inside functions for AddNode*/

const int LENGTH_OF_NIL = 3;
const int SIZE_OF_CMD = 40;
const int SIZE_OF_VAR_BUF = 10;


char * ReadTreeFromFile (Tree_t * tree, FILE * log)
{
    assert(tree);
    assert(log);

    Buffer_t buffer = ReadFileToBuffer();
    char * pos = buffer.data;

    Variable_t * var_buff = AllocateVarBuff();
    if (!var_buff) {printf("ERROR at %s\n", __FUNCTION__); return NULL;}

    fprintf(log, "<strong> ");
    tree->root = ReadNode(tree, &pos, var_buff);
    fprintf(log, "</strong> ");

    SetParent(tree->root);
    free(var_buff);

    return buffer.data;
}


Variable_t * AllocateVarBuff (void)
{
    Variable_t * var_buff = (Variable_t *) calloc (SIZE_OF_VAR_BUF, sizeof(Variable_t));

    return var_buff;
}


void SetParent (Node_t * current)
{
    assert(current);

    if (current->left)
    {
        (current->left)->parent = current;
        SetParent(current->left);
    }
    if (current->right)
    {
        (current->right)->parent = current;
        SetParent(current->right);
    }
}


void OutputBuf (FILE * fp, char ** pos, char  * buffer, Tree_t * tree)
{
    assert(fp);
    assert(pos);
    assert(*pos);
    assert(buffer);
    assert(tree);

    fprintf(fp, "<font color=red> &lt");
    MyFwrite(fp, *pos);
    fprintf(fp, "&gt <font color=black> <br> <br> \n");
}


void MyFwrite (FILE * fp, char * pos)
{
    assert(fp);
    assert(pos);

    while(*pos != '\0')
    {
        switch(*pos)
        {
            case '\0': fputc('\\', fp); fputc('0', fp);  break;
            case '\n': fputc('\\', fp); fputc('n', fp);  break;
            case '\t': fputc('\\', fp); fputc('t', fp);  break;
            case '\b': fputc('\\', fp); fputc('b', fp);  break;
            case '\r': fputc('\\', fp); fputc('r', fp);  break;
            case '\a': fputc('\\', fp); fputc('a', fp);  break;
            case '\\': fputc('\\', fp); fputc('\\', fp); break;
            case '\?': fputc('\\', fp); fputc('?', fp);  break;
            default:   fputc(*pos, fp);
        };
        pos++;
    }
}


Node_t * ReadNode (Tree_t * tree, char ** pos, Variable_t * var_buff)
{
    assert(tree);
    assert(pos);
    assert(*pos);

    FILE * fp = GetLog(tree);
    assert(fp);
    SkipSpaces(pos);

    if (!ReadOpenBrace(**pos)) // skip (
    {
        if (!ReadNil(pos))
            ERROR_IN_TREE_CODE(fp, **pos);
        return NULL;
    }

    IncrementTreeNodeCount(tree);
    Node_t * node = AllocateNodeMemory();
    if (!node)
        return NULL;

    MoveToFirstLetter(pos);
    ReadNodeValue(node, pos, var_buff);
    //CALL_DUMP;
    node->left = ReadNode(tree, pos, var_buff);
    //CALL_DUMP;
    node->right = ReadNode(tree, pos, var_buff);
    //CALL_DUMP;
    SkipSpaces(pos);

    if (!ReadCloseBrace(**pos))
    {
        printf("\nSyntax error: no close brace found. Pos = [%c]\n", **pos);
        fclose(fp);
        return NULL;
    }
    (*pos)++; // move from close brace

    return node;
}


void MoveToFirstLetter (char ** pos)
{
    assert(pos);

    (*pos)++; // move forward from '('
    SkipSpaces(pos);
}


void IncrementTreeNodeCount (Tree_t * tree)
{
    assert(tree);

    tree->size++;
}


Node_t * AllocateNodeMemory (void)
{
    Node_t * node = (Node_t *) calloc (1, sizeof(Node_t));

    return node;
}

bool ReadNil (char ** pos)
{
    assert(pos);
    assert(*pos);

    if (**pos == 'n')
    {
        *pos += LENGTH_OF_NIL;
        SkipSpaces(pos);
        return true;
    }

    return false;
}


bool ReadCloseBrace (char sym)
{
    if (sym == ')')
        return true;
    return false;
}


bool ReadOpenBrace (char sym)
{
    if (sym == '(')
        return true;
    return false;
}


void SkipSpaces (char ** pos)
{
    assert(pos);
    assert(*pos);

    while (isspace(**pos) != 0)
        (*pos)++;
}


void ReadNodeValue (Node_t * node, char ** pos, Variable_t * var_buff)
{
    assert(node);
    assert(pos);
    assert(*pos);

    if (isdigit(**pos))
    {
        node->type = Num_t;
        sscanf(*pos, "%lf", &((node->value).num));
        while (**pos != ' ')
            (*pos)++;
    }
    else if (isalpha(**pos))
    {
        switch(**pos)
        {
            case 's': { if (ReadSin(pos))
                        {
                            node->type = Op_t;
                            (node->value).cmd = SinCmd;
                        }
                        else
                        {
                            if (ReadVarName(node, pos, var_buff) != kNoError)
                                printf("%s: %d: ERROR\n", __FUNCTION__, __LINE__);
                        }
                        break;
                        }

            case 'c': { if (ReadCos(pos))
                       {
                            node->type = Op_t;
                            (node->value).cmd = CosCmd;
                        }
                        else if (ReadCtg(pos))
                        {
                            node->type = Op_t;
                            (node->value).cmd = CtgCmd;
                        }
                        else
                        {
                            if (ReadVarName(node, pos, var_buff) != kNoError)
                                printf("%s: %d: ERROR\n", __FUNCTION__, __LINE__);
                        }
                        break;}

            case 't': { if (ReadTan(pos))
                        {
                            node->type = Op_t;
                            (node->value).cmd = TanCmd;
                        }
                        else
                        {
                            if (ReadVarName(node, pos, var_buff) != kNoError)
                                printf("%s: %d: ERROR\n", __FUNCTION__, __LINE__);
                        }
                        break;}

            case 'a': { if (ReadArcsin(pos))
                        {
                            node->type = Op_t;
                            (node->value).cmd = ArcsinCmd;
                        }
                        else if (ReadArccos(pos))
                        {
                            node->type = Op_t;
                            (node->value).cmd = ArccosCmd;
                        }
                        else if (ReadArctg(pos))
                        {
                            node->type = Op_t;
                            (node->value).cmd = ArctgCmd;
                        }
                        else if (ReadArcctg(pos))
                        {
                            node->type = Op_t;
                            (node->value).cmd = ArcctgCmd;
                        }
                        else
                        {
                            if (ReadVarName(node, pos, var_buff) != kNoError)
                                printf("%s: %d: ERROR\n", __FUNCTION__, __LINE__);
                        }
                        break;}
            case 'l': { if (ReadLn(pos))
                        {
                            node->type = Op_t;
                            (node->value).cmd = LnCmd;
                        }
                        else if (ReadLog(pos))
                        {
                            node->type = Op_t;
                            (node->value).cmd = LogCmd;
                        }
                        else
                        {
                            if (ReadVarName(node, pos, var_buff) != kNoError)
                                printf("%s: %d: ERROR\n", __FUNCTION__, __LINE__);
                        }
                        break;}
            default : { node->type = Var_t;
                        if (ReadVarName(node, pos, var_buff) != kNoError)
                            printf("%s: %d: ERROR\n", __FUNCTION__, __LINE__);}
        }
    }
    else
    {
        node->type = Op_t;
        switch(**pos)
        {
            case '+': (node->value).cmd = AddCmd; break;
            case '*': (node->value).cmd = MulCmd; break;
            case '/': (node->value).cmd = DivCmd; break;
            case '^': (node->value).cmd = PowCmd; break;
            default:  printf("ERROR: pos = [%c]\n", **pos);
        }
        (*pos)++;
    }
}


Err_t ReadVarName (Node_t * node, char ** pos, Variable_t * var_buff)
{
    assert(node);
    assert(pos);
    assert(*pos);
    assert(var_buff);

    (node->value).var.name = **pos;

    bool is_var_found = WriteValueToNodeIfExist(node, var_buff, **pos);
    if (is_var_found)
    {
        (*pos)++;
        return kNoError;
    }

    printf("Введите значение переменной %c: ", ((node->value).var).name);
    if (scanf("%lf", &((node->value).var).value) != 1)
        return kScanfError;

    (*pos)++;

    return kNoError;
}


bool WriteValueToNodeIfExist (Node_t * node, Variable_t * var_buff, char var)
{
    assert(node);
    assert(var_buff);

    static int buf_count = 0;

    for (int count = 0; count < SIZE_OF_VAR_BUF; count++)
    {
        if (var == (var_buff[count]).name)
        {
            (node->value).var.value = (var_buff[count]).value;
            return true;
        }
    }

    (var_buff[buf_count]).name = (node->value).var.name;
    (var_buff[buf_count]).value = (node->value).var.value;
    buf_count++;

    return false;
}


/*char * ReadVarName (char ** pos)
{
    assert(pos);
    assert(*pos);

    char * var_name = (char *) calloc (SIZE_OF_STRING, sizeof(char));
    char * ptr = *pos;
    while (**pos != ' ')
        (*pos)++;
    **pos = '\0';
    strcpy(var_name, ptr);
    **pos = ' ';

    return var_name;
}*/


bool ReadSin (char ** pos)
{
    assert(pos);
    assert(*pos);

    char second_letter = *(*pos + 1);
    char third_letter  = *(*pos + 2);

    if (second_letter == 'i' && third_letter == 'n')
    {
        (*pos)+= LENTH_OF_SIN_WORD;
        return true;
    }

    return false;
}


bool ReadCos (char ** pos)
{
    assert(pos);
    assert(*pos);

    char second_letter = *(*pos + 1);
    char third_letter  = *(*pos + 2);

    if (second_letter == 'o' && third_letter == 's')
    {
        (*pos)+= LENTH_OF_COS_WORD;
        return true;
    }

    return false;
}


bool ReadCtg (char ** pos)
{
    assert(pos);
    assert(*pos);

    char second_letter = *(*pos + 1);
    char third_letter  = *(*pos + 2);

    if (second_letter == 't' && third_letter == 'g')
    {
        (*pos)+= LENTH_OF_CTG_WORD;
        return true;
    }

    return false;
}


bool ReadTan (char ** pos)
{
    assert(pos);
    assert(*pos);

    char second_letter = *(*pos + 1);
    char third_letter  = *(*pos + 2);

    if (second_letter == 'a' && third_letter == 'n')
    {
        (*pos)+= LENTH_OF_TAN_WORD;
        return true;
    }

    return false;
}


bool ReadArcsin (char ** pos)
{
    assert(pos);
    assert(*pos);

    char end_of_word = *(*pos + LENTH_OF_ARCSIN_WORD);

    *(*pos + LENTH_OF_ARCSIN_WORD) = '\0';

    if (strcmp("arcsin", *pos) == 0)
    {
        *(*pos + 6) = end_of_word;
        (*pos)+= LENTH_OF_ARCSIN_WORD;
        return true;
    }

    *(*pos + 6) = end_of_word;

    return false;
}


bool ReadArccos (char ** pos)
{
    assert(pos);
    assert(*pos);

    char end_of_word = *(*pos + LENTH_OF_ARCSIN_WORD);

    *(*pos + LENTH_OF_ARCSIN_WORD) = '\0';

    if (strcmp("arccos", *pos) == 0)
    {
        *(*pos + 6) = end_of_word;
        (*pos)+= LENTH_OF_ARCCOS_WORD;
        return true;
    }

    *(*pos + LENTH_OF_ARCSIN_WORD) = end_of_word;

    return false;
}


bool ReadArctg (char ** pos)
{
    assert(pos);
    assert(*pos);

    char end_of_word = *(*pos + LENTH_OF_ARCTAN_WORD);

    *(*pos + LENTH_OF_ARCTAN_WORD) = '\0';

    if (strcmp("arctg", *pos) == 0)
    {
        *(*pos + 5) = end_of_word;
        (*pos)+= LENTH_OF_ARCTAN_WORD;
        return true;
    }

    *(*pos + LENTH_OF_ARCTAN_WORD) = end_of_word;

    return false;
}


bool ReadArcctg (char ** pos)
{
    assert(pos);
    assert(*pos);

    char * end_of_word = *pos + LENTH_OF_ARCCTG_WORD;

    *end_of_word = '\0';

    if (strcmp("arcctg", *pos) == 0)
    {
        *end_of_word = ' ';
        (*pos)+= LENTH_OF_ARCCTG_WORD;
        return true;
    }

    *end_of_word = ' ';

    return false;
}


bool ReadLn (char ** pos)
{
    assert(pos);
    assert(*pos);

    char second_letter = *(*pos + 1);

    if (second_letter == 'n')
    {
        (*pos)+= LENTH_OF_LN_WORD;
        return true;
    }

    return false;
}


bool ReadLog (char ** pos)
{
    assert(pos);
    assert(*pos);

    char second_letter = *(*pos + 1);
    char third_letter  = *(*pos + 2);

    if (second_letter == 'o' && third_letter == 'g')
    {
        (*pos)+= LENTH_OF_LOG_WORD;
        return true;
    }

    return false;
}


Buffer_t ReadFileToBuffer ()
{
    Buffer_t buffer = {};

    FILE * fp = fopen("output.txt", "r");
    buffer.size = GetFileSize("output.txt");

    buffer.data = (char *) calloc ((size_t)(buffer.size) + 1, sizeof(char));
    assert(buffer.data);

    fread(buffer.data, sizeof(char), (size_t)(buffer.size), fp);
    fclose(fp);

    return buffer;
}
