#ifndef GET_H
#define GET_H

/*Get functions*/
const char * GetPlace     (Place_t place);
char * GetCommand         (char * pic_name);
FILE * GetLog             (Tree_t * tree);
char * GetPicName         (void);
int GetFileSize           (const char * filename);
const char * GetOperation (Calc_t operation);
const char * GetNodeType  (int type);

#endif // GET_H
