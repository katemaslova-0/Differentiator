#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Data.h"
#include "TreeFunc.h"
#include "ReadFunc.h"
#include "GetFunc.h"
#include "GraphDump.h"
#include "PlotDump.h"
#include "LogFunc.h"
#include "DiffFunc.h"
#include "Calculate.h"
#include "StackFunc.h"
#include "LatexDump.h"

#define RETURN_IF_NOT_OPENED(log) if (!log) {OutputErrorCode(kFileOpeningError); return -1;}

const int SIZE_OF_BUF = 10;

int main (void)
{
    FILE * log = fopen("diff.htm", "w");
    RETURN_IF_NOT_OPENED(log);

    FILE * tex = fopen("Dump.tex", "w");
    assert(tex);
    StartLatexCode(tex);

    OutputLogTitle(log);

    Tree_t tree = {};
    tree.log = log; // FIXME function?

    char * buffer = ReadTreeFromFile(&tree, log);

    Tree_t diff_tree = {};
    diff_tree.log  = log; // FIXME function?

    DumpStartExpressionToLatex(tex, &tree);

    if ((diff_tree.root = Differentiate(tex, &tree, tree.root)) == NULL)
    {
        printf("Null root pointer\n");
        return -1;
    }

    SetParent(diff_tree.root);
    OutputResult(Calculate(&diff_tree, diff_tree.root));

    char * plot_before_diff = MakePlotPic(&tree);
    PutPlotToTex(tex, plot_before_diff, "График исходной функции");

    char * plot_after_diff = MakePlotPic(&diff_tree);
    PutPlotToTex(tex, plot_after_diff, "График производной функции");

    EndLatexCode(tex);
    fclose(tex);
    system("pdflatex Dump.tex");

    free(plot_before_diff);
    free(plot_after_diff);
    fclose(log);
    free(buffer);
    //VarNamesDtor(tree.root);
    NodeDtor(tree.root);
    NodeDtor(diff_tree.root);

    return 0;
}
