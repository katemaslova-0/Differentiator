#ifndef LATEX_H
#define LATEX_H

void StartLatexCode (FILE * fp);
void EndLatexCode   (FILE * fp);

void DumpStartExpressionToLatex (FILE * fp, Tree_t * tree);
Node_t * DumpNodeBeforeDiff     (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DumpNodeToLatex        (FILE * fp, Node_t * node);
void OutputPhrase               (FILE * fp);

void DumpAddNodeToLatex    (FILE * fp, Node_t * node);
void DumpMulNodeToLatex    (FILE * fp, Node_t * node);
void DumpDivNodeToLatex    (FILE * fp, Node_t * node);
void DumpSinNodeToLatex    (FILE * fp, Node_t * node);
void DumpCosNodeToLatex    (FILE * fp, Node_t * node);
void DumpTanNodeToLatex    (FILE * fp, Node_t * node);
void DumpCtgNodeToLatex    (FILE * fp, Node_t * node);
void DumpPowNodeToLatex    (FILE * fp, Node_t * node);
void DumpArcsinNodeToLatex (FILE * fp, Node_t * node);
void DumpArccosNodeToLatex (FILE * fp, Node_t * node);
void DumpArctgNodeToLatex  (FILE * fp, Node_t * node);
void DumpArcctgNodeToLatex (FILE * fp, Node_t * node);
void DumpLogNodeToLatex    (FILE * fp, Node_t * node);
void DumpLnNodeToLatex     (FILE * fp, Node_t * node);

#endif // LATEX_H
