#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "list.h"

char* Operators[17] = { "+","-","*","/","%","=","==","!=","<","<=",">",">=","&","&&","||","!","." };
char* Keywords[5] = { "while","else","if","return","num" };
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
		newNode->token.string[count] == 0;
	}
	newNode->PreNode = NULL;
	newNode->NextNode = NULL;
	newNode->size = 0;
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
		node->token.string[count] == 0;
	}
	node->token.type = 0;
	node->size = 0;
}

/*
Insert the node to the list end.
*/
void end_insert_list(Node* pHead, char* val, int x)
{
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
Transform the list from begin to end
*/
void out_front_list(Node* head)
{
	FILE* output;
	output = fopen("output.txt", "w");
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
			for (n = 0; n < 17; n++) {
				strcpy(COMPARE, Operators[n]);
				if (strcmp(COMPARE, p->token.string) == 0) {
					choosen = n;
					switch (choosen) {

					case 0:     fprintf(output, "Operator: PLUS\n");      break;
					case 1:		fprintf(output, "Operator: MINUS\n");     break;
					case 2:		fprintf(output, "Operator: MTPLUS\n");    break;
					case 3:		fprintf(output, "Operator: DEVIDE\n");    break;
					case 4:		fprintf(output, "Operator: MOD\n");       break;
					case 5:		fprintf(output, "Operator: ASSIGN\n");    break;
					case 6:		fprintf(output, "Operator: EQ\n");        break;
					case 7:		fprintf(output, "Operator: NEQ\n");       break;
					case 8:		fprintf(output, "Operator: LT\n");        break;
					case 9:		fprintf(output, "Operator: LE\n");        break;
					case 10:	fprintf(output, "Operator: MT\n");        break;
					case 11:	fprintf(output, "Operator: ME\n");        break;
					case 12:	fprintf(output, "Operator: GETADRESS\n"); break;
					case 13:	fprintf(output, "Operator: AND\n");       break;
					case 14:	fprintf(output, "Operator: OR\n");        break;
					case 15:	fprintf(output, "Operator: INV\n");       break;
					case 16:	fprintf(output, "Operator: DOT\n");       break;
					}
				}

			}
			for (n = 0; n < 5; n++) {
				strcpy(COMPARE, Keywords[n]);
				if (strcmp(p->token.string, COMPARE) == 0) {
					choosen = n;
					switch (choosen) {

					case 0:     fprintf(output, "Keyword: while\n");  break;
					case 1:		fprintf(output, "Keyword: else\n");   break;
					case 2:		fprintf(output, "Keyword: if\n");     break;
					case 3:		fprintf(output, "Keyword: return\n"); break;
					case 4:		fprintf(output, "Keyword: num\n");    break;

					}
				}

			}
			for (n = 0; n < 11; n++) {
				strcpy(COMPARE, Seperators[n]);
				if (strcmp(p->token.string, COMPARE) == 0) {
					choosen = n;
					switch (choosen) {

					case 0:     fprintf(output, "Sperator: LPAR\n");    break;
					case 1:		fprintf(output, "Sperator: RPAR\n");    break;
					case 2:		fprintf(output, "Sperator: LBRKT\n");   break;
					case 3:		fprintf(output, "Sperator: RBRKT\n");   break;
					case 4:		fprintf(output, "Sperator: LINDEX\n");  break;
					case 5:		fprintf(output, "Sperator: RINDEX\n");  break;
					case 6:		fprintf(output, "Sperator: COMMA\n");   break;
					case 7:		fprintf(output, "Sperator: SEMI\n");    break;
					case 8:		fprintf(output, "Sperator: COLON\n");   break;
					case 9:     fprintf(output, "Sperator: ENDFUNC\n"); break;
					case 10:    fprintf(output, "Sperator: BEGFUNC\n"); break;
					}
				}

			}

			if (p->token.type == 2) {
				fprintf(output, "ID: %s\n", p->token.string);
			}
			if (p->token.type == 3) {
				fprintf(output, "NUM: %s\n", p->token.string);
			}
			if (p->token.type == 4) {
				fprintf(output, "Note: %s\n", p->token.string);
			}
			if (p->token.type == 7) {
				fprintf(output, "String: %s\n", p->token.string);
			}
			if (p->token.type == 8) {
				fprintf(output, "ENTER\n");
			}
			if (p->token.type == 9) {
				fprintf(output, "Error!!!");
				exit(1);
			}
			if (p->token.type == 10) {
				fprintf(output, "ENDOFFILE");
			}
			p = p->NextNode;
		}

	}
	fclose(output);
}