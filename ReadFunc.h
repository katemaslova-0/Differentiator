#ifndef READ_H
#define READ_H

/*Inside Read functions*/
Node_t * MakeNewNode       (int value, Type_t type, Node_t * parent);
Node_t * RewriteParentNode (Node_t * node, char * data, Node_t * left, Node_t * right);

Node_t * ReadNode          (Tree_t * tree, char ** pos, Variable_t * var_buff);
void SkipSpaces            (char ** pos);
void ReadNodeValue         (Node_t * node, char ** pos, Variable_t * var_buff);
Buffer_t ReadFileToBuffer  (void);
char * ReadTreeFromFile    (Tree_t * tree, FILE * log);
void SetParent             (Node_t * current);
void OutputBuf             (FILE * fp, char ** pos, char  * buffer, Tree_t * tree);
void MyFwrite              (FILE * fp, char * pos);


bool ReadOpenBrace           (char sym);
bool ReadCloseBrace          (char sym);
bool ReadNil                 (char ** pos);
Node_t * AllocateNodeMemory  (void);
void IncrementTreeNodeCount  (Tree_t * tree);
void MoveToFirstLetter       (char ** pos);
Variable_t * AllocateVarBuff (void);

bool ReadSin    (char ** pos);
bool ReadCos    (char ** pos);
bool ReadTan    (char ** pos);
bool ReadCtg    (char ** pos);
bool ReadArcsin (char ** pos);
bool ReadArccos (char ** pos);
bool ReadArctg  (char ** pos);
bool ReadArcctg (char ** pos);
bool ReadLn     (char ** pos);
bool ReadLog    (char ** pos);

Err_t ReadVarName            (Node_t * node, char ** pos, Variable_t * var_buff);
bool WriteValueToNodeIfExist (Node_t * node, Variable_t * var_buff, char var);
//char * ReadVarName (char ** pos);

#endif // READ_H
