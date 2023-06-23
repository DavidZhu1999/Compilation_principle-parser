/****************************************************
 File: parse_print.c

 Programming designed by the teacher: Liang, Zhiyao
 ****************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "globals.h"



/* macros of  increase/decrease indentation */
//#define INDENT indentNum+=2
//#define UNINDENT indentNum-=2
#define INDENT_GAP 2


static void print_expr_type(ExprType t){
	switch(t) {
	case VOID_TYPE: printf( "void"); break;
	case NUM_TYPE: printf( "NUM"); break;
	case ADDR_TYPE: printf( "address"); break;
	default: printf( "Error ExpType"); break;
	}
}

/* printSpaces indents by printing spaces */
static void print_spaces(int indentNum) {
	int i;
	for (i=0;i<indentNum;i++)
		printf(" ");
}

/* procedure print_tree prints a syntax tree to the
   listing file using indentation to indicate subtrees
   handle FOR_STMT  13/nov/2014
 */
void print_tree( TreeNode * tree ){
	int i;

	/* Variable indentNum is used by printTree to
	 * store current number of spaces to indent
	 */
	static int indentNum = 0;

	indentNum+= INDENT_GAP;
	while (tree != NULL) {
		print_spaces(indentNum); /* Each case only prints one line, If print more than one line, need use printSpaces() first.*/
		//printf("%d ",  tree->lineNum);
		if (tree->nodekind == DCL_ND){
			printf( "Declare:  ");
			print_expr_type(tree->vartype);
			printf( " %s ",tree->ID );
			// print the [size] only if it is an array.
			switch(tree->kind.dcl){
			case ARRAY_DCL:
				printf( "[%s]\n", tree->val );
				break;
			case FUN_DCL:
				printf( "function with parameters :\n");
				// Function parameters will be saved as child[0] of the node
				break;
			case VAR_DCL:
				// do nothing
				printf( "\n");
				break;
			default:
				printf("Unknown DclNode kind\n");
				break;
			}
		}
		else if (tree->nodekind==PARAM_ND){
			printf( "Parameter: ");
			print_expr_type(tree->vartype);
			if(tree->vartype != VOID_TYPE){
				printf(" %s", tree->ID);
				if (tree->kind.param == ARRAY_PARAM)
					printf( "[ ]");
			}
			printf( "\n");
		}
		else if(tree->nodekind==STMT_ND) {
			switch (tree->kind.stmt) {
			case IF_STMT:
				printf("If ");
				if (tree->child[2] != NULL)  // has else part
					printf( " with ELSE \n");
				else
					printf( " without ELSE \n");
				break;
				//  case ITER_STMTMT:
			case WHILE_STMT:
				printf("while stmt: \n");
				break;
				/*
			case FOR_STMT:
				printf("for stmt: \n");
				break;
			case DO_WHILE_STMT:
				printf("do while stmt: \n");
				break;
				*/
			case EXPR_STMT:
				printf("Expression stmt: \n");
				break;
			case CMPD_STMT:
				printf("Compound Stmt:\n");
				break;
			case RTN_STMT:
				printf("Return \n");
				//if there is a return value, it is  child[0].
				break;
				/*
			case NULL_STMT:
				printf( "Null statement:  ;\n");
				break;
				*/
			default:
				printf("Unknown StmtNode kind\n");
				break;
			}
		}
		else if(tree->nodekind==EXPR_ND) {
			switch (tree->kind.exp) {
			case OP_EXPR:
				printf("Operator: ");
				if(strcmp(tree->op, "index") == 0)
					printf( "[] index operator");
				else
					printf("%s", tree->op);
				printf("\n");
				break;
			case CONST_EXPR:
				printf("Const: %s\n",tree->val);
				break;
			case ID_EXPR:
				printf("ID: %s\n",tree->ID);
				break;
			/*
			case ARRAY_EXPR:
				printf("Array: %s, with member index:\n",tree->attr.exprAttr.name);
				break;
			*/
			case CALL_EXPR:
				printf("Call function: %s, with arguments:\n", tree->ID);
				break;
				/* arguments are listed as  child[0]
				  remove ASN_EXP, since it is just an operator expression 13/NOV/2014*/
            //case STR_EXPR:
	        //printf("String: %s\n", tree->ID);
	       //break;
				 
			default:
				printf("Unknown ExpNode kind\n");
				break;
			}
		}
		else printf("Unknown node kind\n");
		for (i=0;i<MAX_CHILDREN;i++)
			print_tree(tree->child[i]);
		tree = tree->Sibling;
	}// end of while loop.
	indentNum -= INDENT_GAP;
}