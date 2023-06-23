/*
CS106 HMK3 Parser
Member name and ID
ZHU ZHEZHAO	   1709853G-I011-0069
ZHAO ZHUOYUE   1709853C-I011-0019
WU XIANG	   17098533-I011-0061
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "globals.h"



//Define global linked list nodes to ensure that the nodes are in the current state
Node* currentnode;



static int isATypeDcl(TYPE1 tokentype)
{
    if ((tokentype == NUM) || (tokentype == VOID))
        return 1;
    else
        return 0;
}


TreeNode *Parse(Node* head){
	TreeNode *HeadTreeNode;
	currentnode = head;
	HeadTreeNode = declaration_list();

	return HeadTreeNode;
}


//for know it is a dclkind, like num.
//if it isn't a declaration say error.
static ExprType matchdclkind(void)
{
	ExprType treenodetype = VOID;
    switch(currentnode->token.type1)
    {
    case NUM:   treenodetype = NUM_TYPE; 
    			currentnode = currentnode->NextNode; 
    			break;
    case VOID: 	treenodetype = VOID_TYPE; 
    			currentnode = currentnode->NextNode; 
    			break;
    default: {
    			printf("Error line %d: don't declaration, %s \n", currentnode->length,currentnode->token.type1);
    			printf("\n");
    			exit(1);
             break;
        }
    }
    return treenodetype;
}

//like (, we need find later node have a ),and make
//current node to next
static void MatchNodeType(TYPE1 CorrectType)
{
    if (currentnode->token.type1 == CorrectType){
        
        currentnode = currentnode->NextNode; 
    }

    else
    {
    	printf("Error line %d: undefined,maybe you lose ; ( )...\n", currentnode->length);
    	printf("\n");		
    	exit(1);        
    }
}

static void MatchEnterNote(TYPE1 CorrectType){
    while((currentnode->token.type1 == ENTER) || (currentnode->token.type1 == NOTE)){
        while(currentnode->token.type1 == ENTER){
            MatchNodeType(ENTER);
        }
        while(currentnode->token.type1 == NOTE){
            MatchNodeType(NOTE);
        }       
    }

}


static TreeNode *declaration_list(void){
	TreeNode *Tree;
	TreeNode *pTree;
    MatchEnterNote(currentnode->token.type1);
	Tree = declaration();
    MatchEnterNote(currentnode->token.type1);
	pTree = Tree;
	while(currentnode->token.type1 != ENDOFFILE){
		TreeNode *tempNode;
        if(currentnode->token.type1 == ID){//call function
            tempNode = id_stmt();
            MatchNodeType(SEMI);
            MatchEnterNote(currentnode->token.type1);
        }else{
            tempNode = declaration();
            MatchEnterNote(currentnode->token.type1);
        }
		if((pTree != NULL) && (tempNode != NULL)){
			pTree->Sibling = tempNode;
			pTree = tempNode;
		}
	}
	return Tree;
}


static TreeNode *declaration(void)
{
	    TreeNode  *Tree = NULL;
	    ExprType   dclType;
	    char      idname[100];
	    dclType = matchdclkind();
	    strcpy(idname,currentnode->token.string);
        MatchEnterNote(currentnode->token.type1);
        if(currentnode->token.type1==ID){
	        MatchNodeType(ID);
            MatchEnterNote(currentnode->token.type1);
        }
	    switch(currentnode->token.type1)
	    {
		    case SEMI:     //variable declaration
		        Tree = NewDclTreeNode(VAR_DCL);

			if(Tree != NULL){
				strcpy(Tree->ID,idname);
				Tree->vartype = dclType;
			}
			MatchNodeType(SEMI);
            MatchEnterNote(currentnode->token.type1);
			break;
			
		    case LINDEX:  	// array declaration
			Tree = NewDclTreeNode(ARRAY_DCL);

			if(Tree != NULL){
				strcpy(Tree->ID,idname);
				Tree->vartype = dclType;
			}
			
			MatchNodeType(LINDEX);
            MatchEnterNote(currentnode->token.type1);
			
			if (Tree != NULL)
                strcpy(Tree->val,currentnode->token.string); 
			MatchNodeType(NUM);
            MatchEnterNote(currentnode->token.type1);
			MatchNodeType(RINDEX);
            MatchEnterNote(currentnode->token.type1);
			MatchNodeType(SEMI);
            MatchEnterNote(currentnode->token.type1);
			break;
			
		    case LPAR:		//function declaration
			Tree = NewDclTreeNode(FUN_DCL);

			if (Tree != NULL)
			{
			    strcpy(Tree->ID,idname);
				Tree->vartype = dclType;
			}
			MatchNodeType(LPAR);
            MatchEnterNote(currentnode->token.type1);
			if (Tree != NULL){
				Tree->child[0] = param_list();
                MatchEnterNote(currentnode->token.type1);
            }
			MatchNodeType(RPAR);
            MatchEnterNote(currentnode->token.type1);
			if ((Tree != NULL) && (currentnode->token.type1 != SEMI)) {
				Tree->child[1] = compound_stmt();
                MatchEnterNote(currentnode->token.type1);  
            }
			break;
		    default:
		    	printf("DEFAULT Error line %d: undefined,maybe you lose ; ( )...\n", currentnode->length);
		    	printf("\n");		
		    	exit(1); 
			break;
	    }
	    return Tree;
}

static TreeNode *var_declaration(void)
{
	    TreeNode  *Tree = NULL;
	    ExprType   dclType;
	    char      idname[100];

		dclType = matchdclkind();  
        
	    strcpy(idname,currentnode->token.string);
        
	    MatchNodeType(ID);
        MatchEnterNote(currentnode->token.type1);
	    switch(currentnode->token.type1)
	    {
	    case SEMI:     //variable declaration
        
		Tree = NewDclTreeNode(VAR_DCL);
        
		if(Tree != NULL){
			strcpy(Tree->ID,idname);
			Tree->vartype = dclType;
		}
		MatchNodeType(SEMI);
        MatchEnterNote(currentnode->token.type1);
		break;
		
	    case LINDEX:	// array declaration
            Tree = NewDclTreeNode(ARRAY_DCL);

            if(Tree != NULL){
                strcpy(Tree->ID,idname);
                Tree->vartype = dclType;
            }
            MatchNodeType(LINDEX);
            MatchEnterNote(currentnode->token.type1);
            if (Tree != NULL) 
                strcpy(Tree->val,currentnode->token.string); 
            MatchNodeType(NUMBER);
            MatchEnterNote(currentnode->token.type1);
            MatchNodeType(RINDEX);
            MatchEnterNote(currentnode->token.type1);
            MatchNodeType(SEMI);
            MatchEnterNote(currentnode->token.type1);
		break;
		
	    default:
		    printf("Error line %d: undefined,maybe you lose ; ( )...\n", currentnode->length);
		   	printf("\n");		
		   	exit(1); 
		break;
	    }

    return Tree;
}

static TreeNode *param(void)
{
	    TreeNode *Tree = NULL;
	    ParamKind ParamType;
	    char     idname[100];

		ParamType = matchdclkind();

	    strcpy(idname,currentnode->token.string);
	   if(ParamType == NUM_TYPE)
	    {
        if(currentnode->token.type1==MTPLUS){
            MatchNodeType(MTPLUS);
            MatchEnterNote(currentnode->token.type1);
            strcpy(idname,currentnode->token.string);
            MatchNodeType(ID);    
            MatchEnterNote(currentnode->token.type1); 
		    Tree = NewParamTreeNode(ARRAY_PARAM);//func(a)
            }
            else{
            ///!!!!
            MatchNodeType(ID);
            MatchEnterNote(currentnode->token.type1);
		    Tree = NewParamTreeNode(VAR_PARAM);//func(1)
            }
        }
		if(Tree != NULL){
			strcpy(Tree->ID,idname);
			Tree->vartype = ParamType;
		}
	    
	    return Tree;
}


static TreeNode *param_list(void)
{
    TreeNode *Tree;
    TreeNode *pTree;
    TreeNode *newNode;


    if (currentnode->token.type1 == VOID)//!!!
    {
        MatchNodeType(VOID);
        MatchEnterNote(currentnode->token.type1);
        return NULL;
    }

    Tree = param();
    MatchEnterNote(currentnode->token.type1);
    pTree = Tree;

    while ((Tree != NULL) && (currentnode->token.type1 == COMMA))//!!!
    {
	MatchNodeType(COMMA);
    MatchEnterNote(currentnode->token.type1);
	newNode = param();
	if (newNode != NULL)
        {
	    pTree->Sibling = newNode;//!!!
	    pTree = newNode;
        }
    }

    return Tree;
}



static TreeNode *compound_stmt(void)
{
    TreeNode *Tree = NULL;

    if(currentnode->token.type1 == BEGFUNC)
    {
    	MatchNodeType(BEGFUNC);
    	MatchEnterNote(currentnode->token.type1);
    	if(currentnode->token.type1 == LBRKT){
	    	MatchNodeType(LBRKT);
	        MatchEnterNote(currentnode->token.type1);
	        if (currentnode->token.type1 != RBRKT)
	        {
	            Tree = NewStmtTreeNode(CMPD_STMT);
	        if (isATypeDcl(currentnode->token.type1)){
	            Tree->child[0] = local_declarations();
	            MatchEnterNote(currentnode->token.type1);
	        }
	            
	        if (currentnode->token.type1 != RBRKT){
	            Tree->child[1] = statement_list();
	            MatchEnterNote(currentnode->token.type1);
	        }
		    if(currentnode->token.type1 == RBRKT){
		        MatchNodeType(RBRKT);//match RBRKT
		        MatchEnterNote(currentnode->token.type1);
		    }	        
	        }
		    if(currentnode->token.type1 == ENDFUNC){
		        MatchNodeType(ENDFUNC);//match RBRKT
		        MatchEnterNote(currentnode->token.type1);
		    }
		    return Tree;      

    	}
        MatchEnterNote(currentnode->token.type1);
    	Tree = NewStmtTreeNode(CMPD_STMT);///!!!
    	if (isATypeDcl(currentnode->token.type1)){
	    	Tree->child[0] = local_declarations();
            MatchEnterNote(currentnode->token.type1); 
        }           
            if (currentnode->token.type1 != ENDFUNC){
	    	Tree->child[1] = statement_list();
            MatchEnterNote(currentnode->token.type1);
        }

    }
    if(currentnode->token.type1 == LBRKT){
        MatchNodeType(LBRKT);
        MatchEnterNote(currentnode->token.type1);
        if (currentnode->token.type1 != RBRKT)
        {
            Tree = NewStmtTreeNode(CMPD_STMT);
        if (isATypeDcl(currentnode->token.type1)){
            Tree->child[0] = local_declarations();
            MatchEnterNote(currentnode->token.type1);
        }
            
        if (currentnode->token.type1 != RBRKT){
            Tree->child[1] = statement_list();
            MatchEnterNote(currentnode->token.type1);
        }
            
        }
    }
    if(currentnode->token.type1 == RBRKT){
        MatchNodeType(RBRKT);//match RBRKT
        MatchEnterNote(currentnode->token.type1);
    }
    if(currentnode->token.type1 == ENDFUNC){
        MatchNodeType(ENDFUNC);//match RBRKT
        MatchEnterNote(currentnode->token.type1);
    }
    return Tree;
}


static TreeNode *local_declarations(void)
{
    TreeNode *Tree;
    TreeNode *pTree;
    TreeNode *newNode;

    //if the next is variable declaration
    if (isATypeDcl(currentnode->token.type1))//!!!
	Tree = var_declaration();
    MatchEnterNote(currentnode->token.type1);
    //the next other variable declaration
    if (Tree != NULL)
    {
	pTree = Tree;

	while (isATypeDcl(currentnode->token.type1))
	{
	    newNode = var_declaration();
        MatchEnterNote(currentnode->token.type1);
	    if (newNode != NULL)
	    {
		pTree->Sibling = newNode;
		pTree = newNode;
	    }
	}
    }

    return Tree;
}

static TreeNode *statement_list(void)
{
    TreeNode *Tree = NULL;
    TreeNode *pTree;
    TreeNode *newNode;
    MatchEnterNote(currentnode->token.type1);
    if ((currentnode->token.type1 != RBRKT) && (currentnode->token.type1 != ENDFUNC)&& (currentnode->token.type1 != ENDOFFILE))
    {
        Tree = statement();
        MatchEnterNote(currentnode->token.type1);
        pTree = Tree;
        while (currentnode->token.type1 != RBRKT && (currentnode->token.type1 != ENDFUNC)&& (currentnode->token.type1 != ENDOFFILE))
        {
            newNode = statement();
            MatchEnterNote(currentnode->token.type1);
            if ((pTree != NULL) && (newNode != NULL))
            {
                pTree->Sibling = newNode;
                pTree = newNode;
            }
        }
    }

 
    return Tree;
}


static TreeNode *statement(void)
{
    TreeNode *Tree = NULL;
    MatchEnterNote(currentnode->token.type1);
    switch(currentnode->token.type1)
    {
    case IF: 
        Tree = selection_stmt();
        MatchEnterNote(currentnode->token.type1);
        break;
    case WHILE: 
        Tree = iteration_stmt();
        MatchEnterNote(currentnode->token.type1);
        break;
    case RETURN:
        Tree = return_stmt();
        MatchEnterNote(currentnode->token.type1);
        break;
    case LBRKT:
        Tree = compound_stmt();
        MatchEnterNote(currentnode->token.type1);
        break;
    case ID:
        Tree = expression_stmt();
        MatchEnterNote(currentnode->token.type1);
        break;
    case SEMI:
        Tree = expression_stmt();
        MatchEnterNote(currentnode->token.type1);
        break;
    case LPAR:
        Tree = expression_stmt();
        MatchEnterNote(currentnode->token.type1);
        break;
    case NUM:
        Tree = expression_stmt();
        MatchEnterNote(currentnode->token.type1);
        break;
    default:
		    printf("Error line %d: undefined,maybe you lose ; ( )...\n", currentnode->length);
		   	printf("\n");		
		   	exit(1); 
        break;
    }

    return Tree;
}

static TreeNode *expression_stmt(void)
{
    TreeNode *Tree = NULL;
    if (currentnode->token.type1 == SEMI){
        MatchNodeType(SEMI);
        
        MatchEnterNote(currentnode->token.type1);
    } 
    else if (currentnode->token.type1 != RBRKT)
    {
        Tree = NewStmtTreeNode(EXPR_STMT);
        Tree->child[0] = expression();
        MatchEnterNote(currentnode->token.type1);
        MatchNodeType(SEMI);
        MatchEnterNote(currentnode->token.type1);
    }

    return Tree;
}

/***
if(expression){
	statement
}
else{
	statement
}
***/
static TreeNode *selection_stmt(void)
{
    TreeNode *Tree;
    TreeNode *expr;
    TreeNode *ifStmt;
    TreeNode *elseStmt = NULL;


    MatchNodeType(IF);
    MatchEnterNote(currentnode->token.type1);

    MatchNodeType(LPAR);
    MatchEnterNote(currentnode->token.type1);
    expr = expression();
    MatchEnterNote(currentnode->token.type1);
    MatchNodeType(RPAR);
    MatchEnterNote(currentnode->token.type1);
    ifStmt = statement();
    MatchEnterNote(currentnode->token.type1);

    if (currentnode->token.type1 == ELSE)
    {
	MatchNodeType(ELSE);
    MatchEnterNote(currentnode->token.type1);
	elseStmt = statement();
    MatchEnterNote(currentnode->token.type1);
    }

    Tree = NewStmtTreeNode(IF_STMT);
    MatchEnterNote(currentnode->token.type1);
    if (Tree != NULL)
    {
	Tree->child[0] = expr;
	Tree->child[1] = ifStmt;
	Tree->child[2] = elseStmt;
    }

    return Tree;
}

/***
while(expression){
	statement
}
****/
static TreeNode *iteration_stmt(void)
{
    TreeNode *Tree;
    TreeNode *expr;
    TreeNode *stmt;

    MatchNodeType(WHILE);
    MatchEnterNote(currentnode->token.type1);
    MatchNodeType(LPAR);
    MatchEnterNote(currentnode->token.type1);
    expr = expression();
    MatchEnterNote(currentnode->token.type1);
    MatchNodeType(RPAR);
    MatchEnterNote(currentnode->token.type1);
    stmt = statement();
    MatchEnterNote(currentnode->token.type1);
    
    Tree = NewStmtTreeNode(WHILE_STMT);
    if (Tree != NULL)
    {
	Tree->child[0] = expr;
	Tree->child[1] = stmt;
    }

    return Tree;
}

/***
return expression;
***/
static TreeNode *return_stmt(void)
{
    TreeNode *Tree;
    TreeNode *expr = NULL;

    MatchNodeType(RETURN);
    MatchEnterNote(currentnode->token.type1);

    Tree = NewStmtTreeNode(RTN_STMT);
    if (currentnode->token.type1 != SEMI) 
	expr = expression();
    MatchEnterNote(currentnode->token.type1);

    if (Tree != NULL) 
	Tree->child[0] = expr;

    MatchNodeType(SEMI);
    MatchEnterNote(currentnode->token.type1);

    return Tree;
}

static TreeNode *expression(void)
{
    TreeNode *Tree = NULL;
    TreeNode *LChildTree = NULL;
    TreeNode *RChildTree = NULL;
 

    if ((currentnode->token.type1 == ID) || (currentnode->token.type1 == STRING))
    {
        LChildTree = id_stmt();
        MatchEnterNote(currentnode->token.type1);
    }

    if (currentnode->token.type1 == ASSIGN)
    {
        if ((LChildTree != NULL) && (LChildTree->nodekind == EXPR_ND) && 
            (LChildTree->kind.exp == ID_EXPR))
        {
            MatchNodeType(ASSIGN);
            MatchEnterNote(currentnode->token.type1);
            RChildTree = expression();

            Tree = NewExpTreeNode(OP_EXPR);
            if (Tree != NULL)
            {
                Tree->child[0] = LChildTree;
                Tree->child[1] = RChildTree;
                strcpy(Tree->op,"ASSIGN");
            }
        }
        else
        { 
		    printf("Error line %d: ASSIGN error", currentnode->length);
		   	printf("\n");		
		   	exit(1); 
        }
    }
    else
        Tree = simple_expression(LChildTree);
        MatchEnterNote(currentnode->token.type1);

    return Tree;
}

static TreeNode *simple_expression(TreeNode *CurTreeNode)
{
    TreeNode *Tree;
    TreeNode *LExpr = NULL;
    TreeNode *RExpr = NULL;
    Node *operator;
    LExpr = additive_expression(CurTreeNode);
    MatchEnterNote(currentnode->token.type1);

    if ((currentnode->token.type1 == LT) || 
    	(currentnode->token.type1 == LE) || 
    	(currentnode->token.type1 == MT) || 
    	(currentnode->token.type1 == ME) || 
    	(currentnode->token.type1 == EQ) || 
    	(currentnode->token.type1 == NEQ))
    {
        operator = currentnode;
        MatchNodeType(currentnode->token.type1);
        MatchEnterNote(currentnode->token.type1);
        RExpr = additive_expression(NULL);
        MatchEnterNote(currentnode->token.type1);

        Tree = NewExpTreeNode(OP_EXPR);
        if (Tree != NULL) 
        {
            Tree->child[0] = LExpr;
            Tree->child[1] = RExpr;
            switch (operator->token.type1)
            {
            case LT: 
                strcpy(Tree->op,"LT");
                break;
            case LE: 
                strcpy(Tree->op,"LE");
                break;            
            case MT: 
                strcpy(Tree->op,"MT");
                break;
            case ME: 
                strcpy(Tree->op,"ME");
                break;
            case EQ: 
                strcpy(Tree->op,"EQ");
                break;
            case NEQ: 
                strcpy(Tree->op,"NEQ");
                break;
            }
        }
    }
    else 
        Tree = LExpr;

    return Tree;
}

static TreeNode *additive_expression(TreeNode *CurTreeNode)
{
    TreeNode *Tree;
    TreeNode *newNode;
    Tree = term(CurTreeNode);
    MatchEnterNote(currentnode->token.type1);

    while ((currentnode->token.type1 == PLUS) || (currentnode->token.type1 == MINUS))
    {
        newNode = NewExpTreeNode(OP_EXPR);
        if (newNode != NULL)
        {
            newNode->child[0] = Tree;
            switch (currentnode->token.type1)
            {
            case PLUS:
                strcpy(newNode->op,"PLUS");
                break;
            case MINUS:
                strcpy(newNode->op,"MINUS");
                break;
            }
            Tree = newNode;
            MatchNodeType(currentnode->token.type1);
            MatchEnterNote(currentnode->token.type1);
            Tree->child[1] = term(NULL);
            MatchEnterNote(currentnode->token.type1);
        }
    }

    return Tree;
}

static TreeNode *term(TreeNode *CurTreeNode)
{
    TreeNode *Tree;
    TreeNode *newNode;
    Tree = factor(CurTreeNode);
    MatchEnterNote(currentnode->token.type1);
    while ((currentnode->token.type1 == MTPLUS) || (currentnode->token.type1 == DEVIDE))//!!!
    {
        newNode = NewExpTreeNode(OP_EXPR);

        if (newNode != NULL)
        {
            newNode->child[0] = Tree;
            switch (currentnode->token.type1)
            {
            case MTPLUS:
                strcpy(newNode->op,"MTPLUS");
                break;
            case DEVIDE:
                strcpy(newNode->op,"DEVIDE");
                break;
            }

            Tree = newNode;
            MatchNodeType(currentnode->token.type1);
            MatchEnterNote(currentnode->token.type1);
            newNode->child[1] = factor(NULL);
            MatchEnterNote(currentnode->token.type1);
        }
    }

    return Tree;
}


static TreeNode *factor(TreeNode *CurTreeNode)
{
    TreeNode *Tree = NULL;
    /* If the subtree in "passdown" is a Factor, pass it back. */
    if (CurTreeNode != NULL)
    {
        return CurTreeNode;
    }
    

    switch (currentnode->token.type1)
    {
    case ID:
        Tree = id_stmt();
        MatchEnterNote(currentnode->token.type1);
        break;
    case LPAR:
        MatchNodeType(LPAR);
        MatchEnterNote(currentnode->token.type1);
        Tree = expression();
        MatchEnterNote(currentnode->token.type1);
        MatchNodeType(RPAR);
        MatchEnterNote(currentnode->token.type1);
        break; 
    case NUMBER:
        Tree = NewExpTreeNode(CONST_EXPR);
        if (Tree != NULL)
        {
            strcpy(Tree->val,currentnode->token.string); 
        }
        MatchNodeType(NUMBER);
        MatchEnterNote(currentnode->token.type1);
        break;
    default:
    		printf("factor Error line %d: undefined,maybe you lose ; ( )...\n", currentnode->length);
		   	printf("\n");		
		   	exit(1); 
        break;
    }
    return Tree;
}


static TreeNode *id_stmt(void)
{
    TreeNode *Tree;
    TreeNode *expr = NULL;
    TreeNode *arguments = NULL;
    char idname[100];
    if (currentnode->token.type1 == ID){
        strcpy(idname,currentnode->token.string);
        MatchNodeType(ID);
        MatchEnterNote(currentnode->token.type1);
    }
    if (currentnode->token.type1 == STRING){
        strcpy(idname,currentnode->token.string);
        MatchNodeType(STRING);
        MatchEnterNote(currentnode->token.type1);
    }
    if (currentnode->token.type1 == LPAR)
    {
        MatchNodeType(LPAR);
        MatchEnterNote(currentnode->token.type1);
        arguments = args();
        MatchEnterNote(currentnode->token.type1);
        MatchNodeType(RPAR);
        MatchEnterNote(currentnode->token.type1);

        Tree = NewExpTreeNode(CALL_EXPR);
        if (Tree != NULL)
        {
            Tree->child[0] = arguments;
            strcpy(Tree->ID,idname);
        }
    }
    else
    {
        if (currentnode->token.type1 == LINDEX)
        {
            MatchNodeType(LINDEX);
            MatchEnterNote(currentnode->token.type1);
            expr = expression(); 
            MatchEnterNote(currentnode->token.type1);
            MatchNodeType(RINDEX);
            MatchEnterNote(currentnode->token.type1);
        }

        Tree = NewExpTreeNode(ID_EXPR);
        if (Tree != NULL)
        {
            Tree->child[0] = expr;
            strcpy(Tree->ID,idname);
            
        }
    }

    return Tree;
}

static TreeNode *args(void)
{
    TreeNode *Tree = NULL;
    if (currentnode->token.type1 != RPAR)
        Tree = arg_list();
        MatchEnterNote(currentnode->token.type1);

    return Tree;
}

static TreeNode *arg_list(void)
{
    TreeNode *Tree;
    TreeNode *pTree;
    TreeNode *newNode;

    Tree = expression();
    MatchEnterNote(currentnode->token.type1);
    pTree = Tree;
    while (currentnode->token.type1 == COMMA)
    {
        MatchNodeType(COMMA);
        MatchEnterNote(currentnode->token.type1);
        newNode = expression();
        MatchEnterNote(currentnode->token.type1);

        if ((pTree != NULL) && (Tree != NULL))
        {
            pTree->Sibling = newNode;
            pTree = newNode;
        }
    }

    return Tree;
}


TreeNode *NewDclTreeNode(DclKind kind)
{
    TreeNode *nodeinfo;

    nodeinfo = mallocNewNode();
    if (nodeinfo)
    {
        nodeinfo->nodekind = DCL_ND;
        nodeinfo->kind.dcl = kind;//!!!
    }

    return nodeinfo;
}

TreeNode *NewParamTreeNode(ParamKind kind)
{
    TreeNode *nodeinfo;

    nodeinfo = mallocNewNode();
    if (nodeinfo)
    {
        nodeinfo->nodekind = PARAM_ND;
        nodeinfo->kind.param = kind;
    }

    return nodeinfo;
}


TreeNode *NewExpTreeNode(ExprKind kind)
{
    TreeNode *nodeinfo;

    nodeinfo = mallocNewNode();
    if (nodeinfo)
    {
        nodeinfo->nodekind = EXPR_ND;
        nodeinfo->kind.exp = kind;
    }

    return nodeinfo;
}

TreeNode *NewStmtTreeNode(StmtKind kind)
{
    TreeNode *nodeinfo;

    nodeinfo = mallocNewNode();
    if (nodeinfo)
    {
        nodeinfo->nodekind = STMT_ND;
        nodeinfo->kind.stmt = kind;
    }

    return nodeinfo;
}


static TreeNode *mallocNewNode(void)
{
    TreeNode *tree;
    int i;


    tree = (TreeNode*)malloc(sizeof(TreeNode));
    if (!tree)
    {
            ("Can't malloc in the line: %d.\n", currentnode->length);
    }
    else
    {
        for (i=0; i < MAX_CHILDREN; ++i) tree->child[i] = NULL;
        tree->Sibling = NULL;
        tree->lineNum = currentnode->length;
    }

    return tree;
}

