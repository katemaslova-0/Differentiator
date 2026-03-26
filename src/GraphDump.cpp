#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "GraphDump.h"
#include "ReadFunc.h"
#include "TreeFunc.h"
#include "GetFunc.h"


Err_t GraphDump (Tree_t * tree, Node_t * node, Place_t place, const char * func_name, const char * file_name, int num_of_line, Node_t * addr, char * value, int result)
{
    assert(tree);
    assert(func_name);
    assert(file_name);

    MakeGraphCodeFile(tree, node);

    char * pic_name = GetPicName();
    if (!pic_name) return kMemAllocError;

    char * command  = GetCommand(pic_name);
    if (!command) return kMemAllocError;

    const char * place_of_call = GetPlace(place);
    FILE * log = GetLog(tree);

    if (system(command) != 0)
        return kSystemError;
    free(command);

    OutputTitle(log, place_of_call, func_name, file_name, num_of_line, addr, value, result);
    OutputImage(log, pic_name);

    free(pic_name);
    return kNoError;
}


Err_t MakeGraphCodeFile (Tree_t * tree, Node_t * node)
{
    assert(tree);

    FILE * fp = fopen("diffdump.txt", "w");
    if (!fp)
        return kFileOpeningError;

    fprintf(fp, "digraph G{\nrankdir=HR;\n");
    if (node != NULL)
        OutputNode(fp, node);
    else
        OutputNode(fp, tree->root);
    fprintf(fp, "}");

    fclose(fp);
    return kNoError;
}


void OutputTitle (FILE * log, const char * place, const char * func_name, const char * file_name, int num_of_line, Node_t * addr, char * value, int result)
{
    assert(log);
    assert(place);
    assert(func_name);
    assert(file_name);
    //assert(value);

    if (strcmp(func_name, "TreeCtor") == 0)
        fprintf(log, "<pre>\n<h3> DUMP <font color=red>%s</font> %s", place, func_name);
    else
    {
        fprintf(log, "<pre>\n<h3> DUMP <font color=red>%s</font> %s %p", place, func_name, addr);
        fprintf(log, " (element = %s) ", value);
    }

    if (result == kDumpSuccess)
        fprintf(log, " <font color=green>(SUCCESS)<font color=black></h3>\n");
    else
        fprintf(log, " <font color=red>(ERROR)<font color=black></h3>\n");
    fprintf(log, "Verified at: %s:%d\n\n\n          ", file_name, num_of_line);
}


void OutputImage (FILE * log, char * pic_name)
{
    assert(log);
    assert(pic_name);

    fprintf(log, "\nIMAGE:\n\n <img src=%s width=800px>\n\n\n", pic_name);
}


void OutputErrorCode (Err_t error)
{
    switch (error)
    {
        case kNoError:                                                break;
        case kMemAllocError:     printf("Memory allocation error\n"); break;
        case kNullNodePointer:   printf("Null node pointer\n");       break;
        case kTwoDads:           printf("Two dads\n");                break;
        case kSimilarChildren:   printf("Similar children\n");        break;
        case kRecursiveOverflow: printf("Recursive overflow\n");      break;
        case kSystemError:       printf("System command failed\n");   break;
        case kFileOpeningError:  printf("File opening error\n");      break;
        case kWrongRightChild:   printf("Wrong right child\n");       break;
        case kWrongLeftChild:    printf("Wrong left child\n");        break;
        case kScanfError:        printf("Scanf error\n");             break;
        default: ;
    }
}
