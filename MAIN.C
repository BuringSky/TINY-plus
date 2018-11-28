/****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE FALSE

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#if !NO_ANALYZE
//#include "analyze.h"
#if !NO_CODE
//#include "cgen.h"
#endif
#endif
#endif

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

main( int argc, char * argv[] )
{ 
	TreeNode* syntaxTree;

	char pgm[120], ch[120];

	int n, flag = 1;//状态标志

	while (flag) {

		switch (flag) {

		case 1:

			printf("-------TINY扩充语言的语法分析-------\n");

			printf("--打开文件：\n");

			printf("1.SAMPLE.TNY\n");

			printf("2.while_test.tny\n");

			printf("3.dowhile_test.tny\n");

			printf("4.for_test.tny\n");

			printf("5.结束程序 \n");

			printf("\n"); printf("\n");

			printf("请选择（1-5）：");

			scanf("%d", &n);

			while (n < 1 || n>5) {

				printf("-----输入有误，请重新输入：\n");

				scanf("%d", &n);

			}

			switch (n) {

			case 1://打开文件SAMPLE.TNY

				source = fopen("SAMPLE.TNY", "r");

				strcpy(pgm, "SAMPLE.TNY"); break;

			case 2://打开文件while_test.tny

				source = fopen("while_test.tny", "r");

				strcpy(pgm, "while_test.tny"); break;

			case 3://打开文件dowhile_test.tny

				source = fopen("dowhile_test.tny", "r");

				strcpy(pgm, "dowhile_test.tny"); break;

			case 4://打开文件for_test.tny

				source = fopen("for_test.tny", "r");

				strcpy(pgm, "for_test.tny"); break;

			case 5://结束程序

			default:

				fclose(source);//关闭文件

				exit(0);

			}

			if (source == NULL) {

				fprintf(stderr, "File %snot found\n", pgm); exit(1);

			}

		case 2:

			printf("*******输入源程序成功!*******\n");

			printf("*******1.查看源程序\n");

			printf("*******2.查看生成语法树\n");

			printf("*******3.返回上一级\n");

			printf("请选择（1-3）：");

			scanf("%d", &n);

			while (n < 1 || n>3) {

				printf("*****输入有误，请重新输入：\n");

				scanf("%d", &n);

			}

			if (n == 3) { flag = 1; fclose(source); break; }

			else {

				flag = 2;

				switch (n) {

				case 1://打开源程序

					while (!feof(source)) {

						if (fgets(ch, 120, source) != 0)printf("%s", ch);

					}

					fseek(source, 0L, 0); break;//读取结束，将文件指针指向头位置

				case 2://查看生成树

					listing = stdout;

					fprintf(listing, "\nTINYCOMPILATION: %s\n", pgm);

					syntaxTree = parse();

					if (TraceParse) {

						fprintf(listing, "\nSyntaxtree:\n");

						printTree(syntaxTree);

					}

					fseek(source, 0L, 0); break;//查看结束，将文件指针指向头位置

				}

			}

		case 3:

			printf("\n");

			printf("*****1.返回上一级\n");

			printf("*****2.结束程序\n");

			printf("请选择（1-2）：");

			scanf("%d", &n);

			while (n < 1 || n>2) {

				printf("*****输入有误，请重新输入：\n");

				scanf("%d", &n);

			}

			if (n == 1)flag = 2;

			else if (n == 2)flag = 0;

		}

	}

	fclose(source);
	//TreeNode * syntaxTree;
//  char pgm[120]; /* source code file name */
//  if (argc != 2)
//    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
//      exit(1);
//    }
//  strcpy(pgm,argv[1]) ;
//  if (strchr (pgm, '.') == NULL)
//     strcat(pgm,".tny");
//  source = fopen(pgm,"r");
//  if (source==NULL)
//  { fprintf(stderr,"File %s not found\n",pgm);
//    exit(1);
//  }
//  listing = stdout; /* send listing to screen */
//  fprintf(listing,"\nTINY COMPILATION: %s\n",pgm);
//#if NO_PARSE
//  while (getToken()!=ENDFILE);
//#else
//  syntaxTree = parse();
//  if (TraceParse) {
//    fprintf(listing,"\nSyntax tree:\n");
//    printTree(syntaxTree);
//  }
//#if !NO_ANALYZE
//  if (! Error)
//  { if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
//    buildSymtab(syntaxTree);
//    if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
//    typeCheck(syntaxTree);
//    if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
//  }
//#if !NO_CODE
//  if (! Error)
//  { char * codefile;
//    int fnlen = strcspn(pgm,".");
//    codefile = (char *) calloc(fnlen+4, sizeof(char));
//    strncpy(codefile,pgm,fnlen);
//    strcat(codefile,".tm");
//    code = fopen(codefile,"w");
//    if (code == NULL)
//    { printf("Unable to open %s\n",codefile);
//      exit(1);
//    }
//    codeGen(syntaxTree,codefile);
//    fclose(code);
//  }
//#endif
//#endif
//#endif
//  fclose(source);
//  return 0;
}

