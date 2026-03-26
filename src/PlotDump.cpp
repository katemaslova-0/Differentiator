#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "Data.h"
#include "PlotDump.h"
#include "GetFunc.h"

const int BUFFER_SIZE = 200;

void PlotDump (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    switch(node->type)
    {
        case Num_t: fprintf(fp, " %lg ", node->value.num); break;
        case Var_t: {if (node->value.var.name == 'x')
                        fprintf(fp, " %c ", node->value.var.name);
                    else
                        fprintf(fp, "%lg ", node->value.var.value);
                    break;}
        case Op_t:
                    {
                        switch(node->value.cmd)
                        {
                            case AddCmd:    DumpAddNodeToPlot    (fp, node); break;
                            case MulCmd:    DumpMulNodeToPlot    (fp, node); break;
                            case DivCmd:    DumpDivNodeToPlot    (fp, node); break;
                            case SinCmd:    DumpSinNodeToPlot    (fp, node); break;
                            case CosCmd:    DumpCosNodeToPlot    (fp, node); break;
                            case TanCmd:    DumpTanNodeToPlot    (fp, node); break;
                            case CtgCmd:    DumpCtgNodeToPlot    (fp, node); break;
                            case PowCmd:    DumpPowNodeToPlot    (fp, node); break;
                            case ArcsinCmd: DumpArcsinNodeToPlot (fp, node); break;
                            case ArccosCmd: DumpArccosNodeToPlot (fp, node); break;
                            case ArctgCmd:  DumpArctgNodeToPlot  (fp, node); break;
                            case ArcctgCmd: DumpArcctgNodeToPlot (fp, node); break;
                            case LogCmd:    DumpLogNodeToPlot    (fp, node); break;
                            case LnCmd:     DumpLnNodeToPlot     (fp, node); break;
                            default: printf("%s: ERROR: no cmd found\n", __FUNCTION__);
                        }
                    break;
                    }
        default: printf("%s: ERROR: no type found\n", __FUNCTION__);
    }
}


void PutPlotToTex (FILE * fp, const char * picture_name, const char * comment)
{
    assert(fp);
    assert(picture_name);
    assert(comment);

    fprintf(fp, "\n\n\\begin{figure}[h!]\n");
    fprintf(fp, "\\centering\n");
    fprintf(fp, "\\includegraphics");
    fprintf(fp, "[width=0.8\\textwidth]{%s}\n", picture_name);
    fprintf(fp, "\\caption{%s}\n", comment);
    fprintf(fp, "\\end{figure}\n\n");
}


char * MakePlotPic (Tree_t * tree)
{
    assert(tree);

    FILE * fp = fopen("PlotDump.txt", "w");
    PlotDump (fp, tree->root);
    fclose(fp);

    int filesize = GetFileSize("PlotDump.txt");

    char function[BUFFER_SIZE] = "";
    FILE * fp_r = fopen("PlotDump.txt", "r");
    fread(function, filesize / sizeof(char), sizeof(char), fp_r);
    fclose(fp_r);

    char * pic_name = GetPicName();
    if (!pic_name) return NULL;

    char * command = MakePlotGeneratingCommand(function, pic_name);
    if (!command) return NULL;

    printf("String: %s\n", command);

    system(command);
    free(command);

    return pic_name;
}


char * MakePlotGeneratingCommand (char * function, char * pic_name)
{
    assert(function);
    assert(pic_name);

    char * string = (char * ) calloc (BUFFER_SIZE, sizeof(char));
    if(!string) return NULL;

    strcat(string, "gnuplot -e \"set terminal png size 400,300; set output '");
    strcat(string, pic_name);
    strcat(string, "'; plot ");
    strcat(string, function);
    strcat(string, "\"");

    return string;
}


void DumpAddNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " (");
    PlotDump(fp, node->left);
    fprintf(fp, ") + (");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpMulNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " (");
    PlotDump(fp, node->left);
    fprintf(fp, ") * (");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpDivNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " (");
    PlotDump(fp, node->left);
    fprintf(fp, ") / (");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpSinNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " sin( ");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpCosNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " cos( ");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpTanNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " tan( ");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpCtgNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " (1 / tg( ");
    PlotDump(fp, node->right);
    fprintf(fp, ")) ");
}


void DumpPowNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " (");
    PlotDump(fp, node->left);
    fprintf(fp, ")**(");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpArcsinNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " asin( ");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpArccosNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " acos( ");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpArctgNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " atan( ");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}


void DumpArcctgNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " atan( 1 / (");
    PlotDump(fp, node->right);
    fprintf(fp, ")) ");
}


void DumpLogNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " log(");
    PlotDump(fp, node->right);
    fprintf(fp, ") / log(");
    PlotDump(fp, node->left);
    fprintf(fp, ") ");
}


void DumpLnNodeToPlot (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " log(");
    PlotDump(fp, node->right);
    fprintf(fp, ") ");
}
