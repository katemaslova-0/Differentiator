#ifndef PLOT_H
#define PLOT_H

void PlotDump                    (FILE * fp, Node_t * node);
char * MakePlotPic               (Tree_t * tree);
void PutPlotToTex                (FILE * fp, const char * picture_name, const char * comment);
char * MakePlotGeneratingCommand (char * function, char * pic_name);

void DumpAddNodeToPlot    (FILE * fp, Node_t * node);
void DumpMulNodeToPlot    (FILE * fp, Node_t * node);
void DumpDivNodeToPlot    (FILE * fp, Node_t * node);
void DumpSinNodeToPlot    (FILE * fp, Node_t * node);
void DumpCosNodeToPlot    (FILE * fp, Node_t * node);
void DumpTanNodeToPlot    (FILE * fp, Node_t * node);
void DumpCtgNodeToPlot    (FILE * fp, Node_t * node);
void DumpPowNodeToPlot    (FILE * fp, Node_t * node);
void DumpArcsinNodeToPlot (FILE * fp, Node_t * node);
void DumpArccosNodeToPlot (FILE * fp, Node_t * node);
void DumpArctgNodeToPlot  (FILE * fp, Node_t * node);
void DumpArcctgNodeToPlot (FILE * fp, Node_t * node);
void DumpLogNodeToPlot    (FILE * fp, Node_t * node);
void DumpLnNodeToPlot     (FILE * fp, Node_t * node);

#endif // PLOT_H
