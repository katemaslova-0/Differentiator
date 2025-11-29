#include <stdio.h>
#include <assert.h>

#include "LogFunc.h"

void OutputLogTitle (FILE * log)
{
    assert(log);

    fprintf(log, "<pre>______________________________________________________________________________");
    fprintf(log, "<pre> <h3> <font color=DeepPink> LOG FILE <font color=black> </h3> </pre>");
    fprintf(log, "______________________________________________________________________________<pre>");
}
