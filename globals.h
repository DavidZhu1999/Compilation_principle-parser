/*
Define some enum for give the token type
*/
typedef enum { NOTHING = 0, PLUS, MINUS, MTPLUS, DEVIDE, MOD, 
               ASSIGN, EQ, NEQ, LT, LE, MT, ME, GETADDRESS, 
			   AND, OR, INV, DOT, WHILE, ELSE, IF, RETURN, 
			   NUM, VOID, LPAR, RPAR, LBRKT, RBRKT, LINDEX, 
			   RINDEX, COMMA, SEMI, COLON, ENDFUNC, BEGFUNC, 
			   ID, NUMBER, NOTE, STRING, ENTER, ERROR, ENDOFFILE }TYPE1;
/*
Define the token content
*/
typedef struct Token {
	char string[100];
	int type;
	TYPE1 type1;
}Token;

/*
Define a Node
*/
typedef struct Node
{
	Token token;
	int size;
	int length;
	struct Node* PreNode;
	struct Node* NextNode;
}Node;


typedef enum {DCL_ND, PARAM_ND, STMT_ND, EXPR_ND} NodeKind;
typedef enum {VAR_DCL, ARRAY_DCL, FUN_DCL} DclKind;
typedef enum {VAR_PARAM, ARRAY_PARAM, VOID_PARAM} ParamKind;
typedef enum {IF_STMT, WHILE_STMT, CMPD_STMT, EXPR_STMT, RTN_STMT} StmtKind;
typedef enum {OP_EXPR, CONST_EXPR, ID_EXPR, CALL_EXPR} ExprKind;
typedef enum {VOID_TYPE, NUM_TYPE, ADDR_TYPE} ExprType;

#define MAX_CHILDREN 4

typedef TYPE1 TokenType;

//define Tree Node for parser

typedef struct TreeNode{
	struct TreeNode* child[MAX_CHILDREN];
	struct TreeNode * Sibling;

  	int lineNum;
  	NodeKind nodekind;

  	union{
        StmtKind        stmt;
        ExprKind        exp;
        DclKind         dcl; 
        ParamKind 		param;
  	}	kind;

  	char    	 op[100];
  	char         val[100];
  	char         ID[100];
    ExprType     vartype;

}TreeNode;


static int isATypeDcl(TYPE1 tokentype);
TreeNode *Parse(Node* head);
static ExprType matchdclkind(void);
static void MatchNodeType(TYPE1 CorrectType);
static void MatchEnterNote(TYPE1 CorrectType);
static TreeNode *declaration_list(void);
static TreeNode *declaration(void);
static TreeNode *var_declaration(void);
static TreeNode *param(void);
static TreeNode *param_list(void);
static TreeNode *compound_stmt(void);
static TreeNode *local_declarations(void);
static TreeNode *statement_list(void);
static TreeNode *statement(void);
static TreeNode *expression_stmt(void);
static TreeNode *selection_stmt(void);
static TreeNode *iteration_stmt(void);
static TreeNode *return_stmt(void);
static TreeNode *expression(void);
static TreeNode *simple_expression(TreeNode *CurTreeNode);
static TreeNode *additive_expression(TreeNode *CurTreeNode);
static TreeNode *term(TreeNode *CurTreeNode);
static TreeNode *factor(TreeNode *CurTreeNode);
static TreeNode *id_stmt(void);
static TreeNode *args(void);
static TreeNode *arg_list(void);
TreeNode *NewDclTreeNode(DclKind kind);
TreeNode *NewParamTreeNode(ParamKind kind);
TreeNode *NewExpTreeNode(ExprKind kind);
TreeNode *NewStmtTreeNode(StmtKind kind);
static TreeNode *mallocNewNode(void);


Node* create_node(void);
Node* create_list(int n);
void end_insert_list(Node* pHead, char* val, int x);
void ClearNode(Node* node);
void Scanner(char* filename, Node* head);
void Data_Deal(Node* head);
void out_front_list(Node* head);

void print_tree( TreeNode * tree);

static void print_expr_type(ExprType t);

static void print_spaces(int indentNum);