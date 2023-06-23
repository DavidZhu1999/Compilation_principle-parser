#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "globals.h"

char* Operators[19] = { "+","-","*","/","%","=","==","!=","<","<=",">",">=","&","&&","||","!",".", "-->", ":)"};
char* Keywords[6] = { "while","else","if","return","num","void" };
char* Seperators[11] = { "(",")","{","}","[","]",",",";",":",":)","-->" };
/*
Create a new blank node
*/




Node* create_node(void)
{
	Node* newNode;
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("Dynamic memory allocation failed£¡\n");
		exit(0);
	}
	int count;

	/*
	Clean the array string.
	*/

	for (count = 0; count <= 99; count++) {
		newNode->token.string[count] = 0;
	}
	newNode->PreNode = NULL;
	newNode->NextNode = NULL;
	newNode->size = 0;
	newNode->token.type1 = NOTHING;
	return (newNode);
}

/*
Create a list
*/
Node* create_list(int n)
{
	Node* p, * new1, * head;
	p = create_node();
	head = create_node();
	int i;
	if (n >= 1)                    //If the node >= 1, create the first node
	{
		new1 = create_node();
		head = new1;
		p = new1;
	}
	for (i = 2; i <= n; i++)      //After the creating the first node, create the leftover node
	{
		new1 = create_node();
		p->NextNode = new1;
		new1->PreNode = p;
		p = new1;
	}

	if (n >= 1)
		return (head);
	else
		return 0;
}

/*
Clean the Node
*/
void ClearNode(Node* node) {
	node->NextNode = NULL;
	node->PreNode = NULL;
	int count;
	for (count = 0; count <= 99; count++) {
		node->token.string[count] = 0;
	}
	node->token.type = 0;
	node->size = 0;
}

/*
Insert the node to the list end.
*/
void end_insert_list(Node* pHead, char* val, int x)
{
	pHead->length = pHead->length + 1;
	Node* r = pHead;
	Node* pNew = (Node*)malloc(sizeof(Node)); //Generate a new node
	if (pNew == NULL)
	{
		printf("New node allocation failed£¡Program terminates£¡ \n");
		exit(-1);
	}
	strcpy(pNew->token.string, val);
	pNew->token.type = x;
	pNew->NextNode = NULL;

	while (r->NextNode != NULL) //Let the tail pointer loop until the last node
	{
		r = r->NextNode;
	}
	r->NextNode = pNew;
	r = pNew;
}

/*
Data_Deal
*/
void Data_Deal(Node* head)
{
		int n;
		char COMPARE[20];
		Node* p;
		p = head;
		int choosen;
		while (p != NULL)
		{
			if (p->token.type == 5) {
				for (n = 0; n < 19; n++) {
					strcpy(COMPARE, Operators[n]);
					if (strcmp(COMPARE, p->token.string) == 0) {
						choosen = n;
						switch (choosen) {

						case 0:     p->token.type1 = PLUS;      break;
						case 1:		p->token.type1 = MINUS;     break;
						case 2:		p->token.type1 = MTPLUS;    break;
						case 3:		p->token.type1 = DEVIDE;    break;
						case 4:		p->token.type1 = MOD;       break;
						case 5:		p->token.type1 = ASSIGN;    break;
						case 6:		p->token.type1 = EQ;        break;
						case 7:		p->token.type1 = NEQ;       break;
						case 8:		p->token.type1 = LT;        break;
						case 9:		p->token.type1 = LE;        break;
						case 10:	p->token.type1 = MT;        break;
						case 11:	p->token.type1 = ME;        break;
						case 12:	p->token.type1 = GETADDRESS; break;
						case 13:	p->token.type1 = AND;       break;
						case 14:	p->token.type1 = OR;        break;
						case 15:	p->token.type1 = INV;       break;
						case 16:	p->token.type1 = DOT;       break;
						case 17:    p->token.type1 = BEGFUNC;   break;
						case 18:	p->token.type1 = ENDFUNC;   break;
						}
					}

				}
			}

			if (p->token.type == 1) {
				for (n = 0; n < 6; n++) {
					strcpy(COMPARE, Keywords[n]);
					if (strcmp(p->token.string, COMPARE) == 0) {
						choosen = n;
						switch (choosen) {

						case 0:     p->token.type1 = WHILE;  break;
						case 1:		p->token.type1 = ELSE;   break;
						case 2:		p->token.type1 = IF;     break;
						case 3:		p->token.type1 = RETURN; break;
						case 4:		p->token.type1 = NUM;    break;
						case 5:		p->token.type1 = VOID;    break;

						}
					}

				}
			}
			if (p->token.type == 6) {
				for (n = 0; n < 11; n++) {
					strcpy(COMPARE, Seperators[n]);
					if (strcmp(p->token.string, COMPARE) == 0) {
						choosen = n;
						switch (choosen) {

						case 0:     p->token.type1 = LPAR;    break;
						case 1:		p->token.type1 = RPAR;    break;
						case 2:		p->token.type1 = LBRKT;   break;
						case 3:		p->token.type1 = RBRKT;   break;
						case 4:		p->token.type1 = LINDEX;  break;
						case 5:		p->token.type1 = RINDEX;  break;
						case 6:		p->token.type1 = COMMA;   break;
						case 7:		p->token.type1 = SEMI;    break;
						case 8:		p->token.type1 = COLON;   break;
						case 9:     p->token.type1 = ENDFUNC; break;
						case 10:    p->token.type1 = BEGFUNC; break;
						}
					}

				}
			}

			if (p->token.type == 2) {
				p->token.type1 = ID;
			}
			if (p->token.type == 3) {
				p->token.type1 = NUMBER;
			}
			if (p->token.type == 4) {
				p->token.type1 = NOTE;
			}
			if (p->token.type == 7) {
				p->token.type1 = STRING;
			}
			if (p->token.type == 8) {
				p->token.type1 = ENTER;
			}
			if (p->token.type == 9) {
				p->token.type1 = ERROR;
				printf("ERROR!!!!!!!");
				exit(1);
			}
			if (p->token.type == 10) {
				p->token.type1 = ENDOFFILE;
			}
			p = p->NextNode;
		}

	}
/*
transform
*/

void out_front_list(Node* head)
{

	printf("\n\n\nThis is the token list obtained by the scanner:\n\n");
	
	if (head == NULL)
	{
		printf("Error input, the link dosen't exist£¡\n");
	}
	else
	{
		int n;
		char COMPARE[20];
		Node* p;
		p = head;
		int choosen;
		while (p != NULL)
		{
			if (p->token.type == 5) {
				for (n = 0; n < 17; n++) {
					strcpy(COMPARE, Operators[n]);
					if (strcmp(COMPARE, p->token.string) == 0) {
						choosen = n;
						switch (choosen) {

						case 0:     printf("Operator: PLUS\n");      break;
						case 1:		printf("Operator: MINUS\n");     break;
						case 2:		printf("Operator: MTPLUS\n");    break;
						case 3:		printf("Operator: DEVIDE\n");    break;
						case 4:		printf("Operator: MOD\n");       break;
						case 5:		printf("Operator: ASSIGN\n");    break;
						case 6:		printf("Operator: EQ\n");        break;
						case 7:		printf("Operator: NEQ\n");       break;
						case 8:		printf("Operator: LT\n");        break;
						case 9:		printf("Operator: LE\n");        break;
						case 10:	printf("Operator: MT\n");        break;
						case 11:	printf("Operator: ME\n");        break;
						case 12:	printf("Operator: GETADRESS\n"); break;
						case 13:	printf("Operator: AND\n");       break;
						case 14:	printf("Operator: OR\n");        break;
						case 15:	printf("Operator: INV\n");       break;
						case 16:	printf("Operator: DOT\n");       break;
						}
					}

				}
			}

			if (p->token.type == 1) {
				for (n = 0; n < 5; n++) {
					strcpy(COMPARE, Keywords[n]);
					if (strcmp(p->token.string, COMPARE) == 0) {
						choosen = n;
						switch (choosen) {

						case 0:     printf("Keyword: WHILE\n");  break;
						case 1:		printf("Keyword: ELSE\n");   break;
						case 2:		printf("Keyword: IF\n");     break;
						case 3:		printf("Keyword: RETURN\n"); break;
						case 4:		printf("Keyword: NUM\n");    break;
						case 5:		printf("Keyword: VOID\n");    break;
						}
					}

				}
			}

			if (p->token.type == 6) {
				for (n = 0; n < 11; n++) {
					strcpy(COMPARE, Seperators[n]);
					if (strcmp(p->token.string, COMPARE) == 0) {
						choosen = n;
						switch (choosen) {

						case 0:     printf("Sperator: LPAR\n");    break;
						case 1:		printf("Sperator: RPAR\n");    break;
						case 2:		printf("Sperator: LBRKT\n");   break;
						case 3:		printf("Sperator: RBRKT\n");   break;
						case 4:		printf("Sperator: LINDEX\n");  break;
						case 5:		printf("Sperator: RINDEX\n");  break;
						case 6:		printf("Sperator: COMMA\n");   break;
						case 7:		printf("Sperator: SEMI\n");    break;
						case 8:		printf("Sperator: COLON\n");   break;
						case 9:     printf("Sperator: ENDFUNC\n"); break;
						case 10:    printf("Sperator: BEGFUNC\n"); break;
						}
					}

				}
			}

			if (p->token.type == 2) {
				printf("ID: %s\n", p->token.string);
			}
			if (p->token.type == 3) {
				printf("NUMBER: %s\n", p->token.string);
			}
			if (p->token.type == 4) {
				printf("Note: %s\n", p->token.string);
			}
			if (p->token.type == 7) {
				printf("String: %s\n", p->token.string);
			}
			if (p->token.type == 8) {
				printf("ENTER\n");
			}
			if (p->token.type == 9) {
				printf("Error!!!");
				exit(1);
			}
			if (p->token.type == 10) {
				printf("ENDOFFILE");
			}
			p = p->NextNode;
		}
		
	}

}