#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "GraphDump.h"
#include "LatexDump.h"
#include "GetFunc.h"

const int NUM_OF_PHRASES = 9;
const char * phrases[NUM_OF_PHRASES] =
{"В оригинале этой задачи этого условия не было, но поскольку вы слабы разумом, я его добавил\n",
"Об этом мы сможем говорить в 11 классе, если живы будете\n",
"На первом курсе мне экзаменатор задал эту задачу, но не эту. Я её, естественно, не решил\n",
"Меня исправлять - себе вредить\n",
"Не знаю ничего про учебник, я их не читаю. Я их сам пишу\n",
"Это ДИКИЙ интеграл, не надо его писать. Я его один раз напишу\n",
"В вашем учебнике это написано достаточно хреново\n",
"Оценка на букву х - четыре\n",
"Обратите внимание на моё ангельское терпение\n"};


void StartLatexCode (FILE * fp)
{
    assert(fp);

    fprintf(fp, "\\documentclass{article}\n");
    fprintf(fp, "\\usepackage[utf8x]{inputenc}\n");
    fprintf(fp, "\\usepackage[russian]{babel}\n");
    fprintf(fp, "\\usepackage{graphicx}\n");
    fprintf(fp, "\\title{Краткий отчёт о вычислениях производных функций}\n");
    fprintf(fp, "\\author{Postal Dude}\n");
    fprintf(fp, "\\date{November 2025}\n");
    fprintf(fp, "\\begin{document}\n");
    fprintf(fp, "\\maketitle\n");
    fprintf(fp, "\\newpage\n");
    fprintf(fp, "\\section{Вступление}\n");
    fprintf(fp, "\\hspace{5mm} ");
    fprintf(fp, "Вступления пока нет, но оно скоро появится.\n");
    fprintf(fp, "\\section{Преобразования}\n");
}


void EndLatexCode (FILE * fp)
{
    assert(fp);

    fprintf(fp, "\n\\section{Вывод}\n");
    fprintf(fp, "Концовки пока нет, но она скоро появится\n\\\\\\\\\\\\\\\\\n");
    fprintf(fp, "Список литературы на лето и не только:\\\\\\\\\n");
    fprintf(fp, "1) Л. Г. Петерсон \"Математика. 2 класс. Углублённый уровень\"\\\\\n");
    fprintf(fp, "2) Лекция профессора А. С. Багирова \"МАТЕМАТИКА - ЛЖЕНАУКА И ИНСТРУМЕНТ\"");
    fprintf(fp, "ВЛИЯНИЯ ЯЩЕРСКОЙ ЦИВИЛИЗАЦИИ\": ");
    fprintf(fp, "\\\\ https://www.youtube.com/watch?v=V6G3sPbgubY \\\\\n");
    fprintf(fp, "3) С. Лем \"Солярис\"\\\\\n\\end{document}");
}


Node_t * DumpNodeBeforeDiff (FILE * fp, Tree_t * tree, Node_t * node)
{
    assert(tree); // FIXME: this arg is only passed because of graphdump(
    assert(fp);

    GraphDump(tree, node, After, __FUNCTION__, __FILE__, __LINE__, NULL, NULL, kDumpSuccess);

    if (node)
    {
        fprintf(fp, "\\[\\frac{d(");
        DumpNodeToLatex(fp, node);
        fprintf(fp, ")}{dx} ");
    }

    return node;
}


Node_t * DumpNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    switch(node->type)
    {
        case Num_t: fprintf(fp, " %lg ", node->value.num);     break;
        case Var_t: fprintf(fp, " %c ", node->value.var.name); break;
        case Op_t:
                    {
                        switch(node->value.cmd)
                        {
                            case AddCmd:    DumpAddNodeToLatex   (fp, node); break;
                            case MulCmd:    DumpMulNodeToLatex   (fp, node); break;
                            case DivCmd:    DumpDivNodeToLatex   (fp, node); break;
                            case SinCmd:    DumpSinNodeToLatex   (fp, node); break;
                            case CosCmd:    DumpCosNodeToLatex   (fp, node); break;
                            case TanCmd:    DumpTanNodeToLatex   (fp, node); break;
                            case CtgCmd:    DumpCtgNodeToLatex   (fp, node); break;
                            case PowCmd:    DumpPowNodeToLatex   (fp, node); break;
                            case ArcsinCmd: DumpArcsinNodeToLatex(fp, node); break;
                            case ArccosCmd: DumpArccosNodeToLatex(fp, node); break;
                            case ArctgCmd:  DumpArctgNodeToLatex (fp, node); break;
                            case ArcctgCmd: DumpArcctgNodeToLatex(fp, node); break;
                            case LogCmd:    DumpLogNodeToLatex   (fp, node); break;
                            case LnCmd:     DumpLnNodeToLatex    (fp, node); break;
                            default: printf("%s: ERROR: no cmd found\n", __FUNCTION__);
                        }
                        break;
                    }
        default: printf("%s: ERROR: no type found\n", __FUNCTION__);
    }

    return node;
}


void DumpAddNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " (");
    DumpNodeToLatex(fp, node->left);
    fprintf(fp, ") + (");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpMulNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " (");
    DumpNodeToLatex(fp, node->left);
    fprintf(fp, ") * (");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpDivNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " \\frac{");
    DumpNodeToLatex(fp, node->left);
    fprintf(fp, "}{");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, "} ");
}


void DumpSinNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " sin( ");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpCosNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " cos( ");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpTanNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " tan( ");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpCtgNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " ctg( ");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpPowNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " (");
    DumpNodeToLatex(fp, node->left);
    fprintf(fp, ")^{");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, "} ");
}


void DumpArcsinNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " arcsin( ");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpArccosNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " arccos( ");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpArctgNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " arctg( ");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpArcctgNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " arcctg( ");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpLogNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " \\log_");
    DumpNodeToLatex(fp, node->left);
    fprintf(fp, "(");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpLnNodeToLatex (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, " \\ln (");
    DumpNodeToLatex(fp, node->right);
    fprintf(fp, ") ");
}


void DumpStartExpressionToLatex (FILE * fp, Tree_t * tree)
{
    assert(fp);
    assert(tree);

    fprintf(fp, "\\begin{center}\n");
    fprintf(fp, "Исходное выражение: \\[");
    DumpNodeToLatex(fp, tree->root);
    fprintf(fp, "\\]\\\n\\end{center}\n");
}


void OutputPhrase (FILE * fp)
{
    assert(fp);

    int num_of_phrase = rand() % NUM_OF_PHRASES;

    fprintf(fp, "%s\n", phrases[num_of_phrase]);
}
