#ifndef DUMP_H
#define DUMP_H

/*Dump functions*/
void OutputTitle        (FILE * log, const char * place, const char * func_name, const char * file_name, int num_of_line, Node_t * addr, char * value, int result);
void OutputImage        (FILE * log, char * pic_name);
void OutputErrorCode    (Err_t error);
Err_t MakeGraphCodeFile (Tree_t * tree, Node_t * node);
Err_t GraphDump         (Tree_t * tree, Node_t * node, Place_t place, const char * func_name, const char * file_name, int num_of_line, Node_t * addr, char * value, int result);

#endif // DUMP_H
