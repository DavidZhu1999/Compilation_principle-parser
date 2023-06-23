CS106 HMK3 Parser
Member name and ID
ZHU ZHEHAO	1709853G-I011-0069
ZHAO ZHUOYUE	1709853C-I011-0019
WU XINAG	17098533-I011-0061
--------------------------------------------------------------
Promblem:
When it runs sum100.n, it happens error that can't scanner correct information,
but when it runs sum100.txt, it well.
So we suggest using it runs files in .txt.
We think --> and :) is a kind of compound-stmt.
We think String is a kind of parameter for calling function,
so in our syntax tree, we call it ID.
--------------------------------------------------------------
1.How to compile:
Enter the folder Parser at command line, and use the command: 
gcc list.c Parser.c Print_Parser.c scanner.c token.c globals.h

2.How to run:
Enter the Parser folder at command line, use the command: a.exe
--------------------------------------------------------------
BNF Grammar of the Syntax of N language.
Thinking derives from C-
"":explain

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
program -> declaration-list
declaration-list -> declaration | id-stmt "here is for call function"
declaration -> var-declaration | fun-declaration 
var-declaration -> type-specifier ID | type-specifier ID[]
type-specifier -> num | void
fun-declaration ->  type-speciﬁer ID ( params ) compound-stmt | param_list
param_list -> param
param -> type-speciﬁer ID | type-speciﬁer *ID
compound-stmt ->  local-declarations | statement-list
local-declarations ->  var-declaration | empty 
statement-list -> statement | empty 
statement -> selection-stmt |  iteration-stmt | return-stmt | expression-stmt
selection-stmt -> if (expression ) statement | if (expression ) statement else statement 
iteration-stmt ->  while ( expression ) statement 
 return-stmt -> return ; | return expression ; 
expression-stmt -> expression
expression -> id_stmt | simple-exprssion | expression
simple-exprssion -> additive-expression relop additive-expression | additive-expression 
relop -> <= | < | > | >= | == | !=
additive-expression -> additive-expression addop term | term
addop -> + | -
term -> term mulop factor | factor 
mulop -> * | / 
 factor -> expression | const | id-stmt | var
id-stmt ->  ID (args) 
args -> arg-list | empty
arg-list -> expression | empty