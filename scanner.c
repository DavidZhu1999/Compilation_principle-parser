/*
CS106 HMK2 Scanner
Member name and ID
ZHU zhehao	1709853G-I011-0069
ZHAO zhuoyue	1709853C-I011-0019
WU xiang	17098533-I011-0061
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "globals.h"



int main()
{

	Node* head = create_list(1);
	TreeNode *TreeHead;
	FILE* output;
	char filename[20];
	head->length = 0;
	printf("What is the file name? (Hint: arrayMaxMean.n or fact.n or sum100.n)\n");
	gets(filename);
	Scanner(filename, head);
	Data_Deal(head);
	out_front_list(head);
	printf("\n\n\nNow printing parse tree of the parser:\n\n");
	TreeHead = Parse(head->NextNode);
	print_tree(TreeHead);
	return 0;

}