#ifndef DATA_H
#define DATA_H

#define light_green "\"#C0FFC0\""
#define dark_green  "\"#008000\""
#define light_pink  "\"#ffc0f6ff\""
#define dark_pink   "\"#fa5d82ff\""
#define light_red   "\"#ff0000ff\""
#define dark_red    "\"#bd2222ff\""
#define white       "\"#ffffffff\""

const int SIZE_OF_STRING = 40;
const int STACK_SIZE = 10;

#define TREE_VERIFY(tree, place, addr, value) if (NodeVerify(tree->root, tree) != NoError) \
                                            {printf("TreeDump at %s:%d\n", __FILE__, __LINE__); \
                                            Err_t error = NodeVerify(tree->root, tree); \
                                            OutputErrorCode(error); \
                                            GraphDump(tree, NULL, place, __FUNCTION__, __FILE__, __LINE__, addr, value, ERROR); \
                                            return error;} \
                                            GraphDump(tree, NULL, place, __FUNCTION__, __FILE__, __LINE__, addr, value, SUCCESS);

enum Type_t
{
    Num_t = 0,
    Var_t = 1,
    Op_t  = 2
};

enum Calc_t
{
    AddCmd    = 0,
    MulCmd    = 1,
    DivCmd    = 2,
    SinCmd    = 3,
    CosCmd    = 4,
    TanCmd    = 5,
    CtgCmd    = 6,
    PowCmd    = 7,
    ArcsinCmd = 8,
    ArccosCmd = 9,
    ArctgCmd  = 10,
    ArcctgCmd = 11,
    LnCmd     = 12,
    LogCmd    = 13,
};

struct Buffer_t
{
    char * data;
    int size;
};

struct Variable_t
{
    char name;
    double value;
};

union Value_t
{
    Calc_t cmd;
    double num;
    Variable_t var;
};

struct Node_t
{
    Value_t value = {};
    Type_t type;
    Node_t * left;
    Node_t * right;
    Node_t * parent;
};

struct Tree_t
{
    Node_t * root;
    int size;
    FILE * log;
    char ** var_buf; // FIXME: struct Differentiator
};

enum Place_t
{
    NoArg  = 0,
    Before = 1,
    After  = 2
};

enum DumpErrors_t
{
    kDumpSuccess = 0,
    kDumpError   = 1
};

enum Err_t
{
    kNoError           = 0,
    kMemAllocError     = 1,
    kNullNodePointer   = 2,
    kTwoDads           = 3,
    kSimilarChildren   = 4,
    kRecursiveOverflow = 5,
    kSystemError       = 6,
    kFileOpeningError  = 7,
    kWrongRightChild   = 8,
    kWrongLeftChild    = 9,
    kScanfError        = 10
};

#endif // DATA_H
