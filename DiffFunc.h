#ifndef DIFF_H
#define DIFF_H

Node_t * Differentiate (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * MakeNewNode (Type_t type, Value_t value, Node_t * left, Node_t * right);
Node_t * CopyNode (Node_t * node);

Node_t * DiffNum (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffVar (FILE * fp, Tree_t * tree, Node_t * node);

Node_t * DiffAdd (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffMul (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffDiv (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffSin (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffCos (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffTan (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffCtg (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffPow (FILE * fp, Tree_t * tree, Node_t * node);

Node_t * DiffArcsin (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffArccos (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffArctg  (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffArcctg (FILE * fp, Tree_t * tree, Node_t * node);

Node_t * DiffLog (FILE * fp, Tree_t * tree, Node_t * node);
Node_t * DiffLn  (FILE * fp, Tree_t * tree, Node_t * node);

#endif // DIFF_H
