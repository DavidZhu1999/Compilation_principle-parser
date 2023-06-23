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
#include "list.h"


int main()
{

	Node* head = create_list(1);
	FILE* output;
	char filename[20];

	printf("what is the file name:\n");
	gets_s(filename, 20);

	Scanner(filename, head);

	printf("Successful! Please see the file output.txt.");
	out_front_list(head);
	return 0;

}


