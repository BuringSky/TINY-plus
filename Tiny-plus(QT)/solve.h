#ifndef SOLVE_H
#define SOLVE_H

#include "globals.h"
#include "util.h"
#include "parse.h"
#include "scan.h"

#include <QDebug>
int lineno = 0;
FILE * source;
FILE * listing;


/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = TRUE;
int TraceParse = TRUE;

int Error = FALSE;

void syntree()
{
   TreeNode * syntaxTree;
   qDebug()<<"刚进入SYNTREE";
   char pgm[]="source.txt";
   source = fopen(pgm,"rt");
   qDebug()<<"未调用";
   syntaxTree = parse();
   qDebug()<<"已经调用";
   char ch[]="syntaxTree.txt";  //语法树输出文件
   listing  = fopen(ch,"wt+");
   fprintf(listing,"Syntax tree:\n");
   qDebug()<<"嘿";
   printTree(syntaxTree);
   qDebug()<<"哈";
   fclose(listing);
   fclose(source);
}

#endif // SOLVE_H
