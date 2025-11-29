#ifndef TREE_H
#define TREE_H

/*Ctor, Dtor, Verify, Dump*/
Err_t TreeCtor    (Tree_t * tree, FILE * log);
Err_t NodeVerify  (Node_t * node, Tree_t * tree, int count);
void  NodeDtor    (Node_t * node);
//void VarNamesDtor (Node_t * node);

/*Node functions*/
void SetRoot     (Tree_t * tree);
void OutputNode  (FILE * fp, Node_t * node);

#endif // TREE_H
