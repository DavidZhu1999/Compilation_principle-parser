#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "list.h"
/*
Scanner function
*/
void Scanner(FILE* filename, Node* head) {

	FILE* inputFile = filename;
	int count = 1;
	inputFile = fopen(filename, "r");
	if (inputFile == NULL) {
		printf("Sorry, you input a error filename so we cannot find it. Please open the exe again.");
		exit(0);
	}
	char Gets = 'a';

	while (!feof(inputFile)) {
		Node* newNode = create_node();
		ClearNode(newNode);

	F0:Gets = fgetc(inputFile);

		/*
		Judge whether the token is space
		*/
		if (Gets == ' ' || Gets == '\t') {
			goto F0;
		}

		/*
		Judge whether the token is Enter
		*/
		else if (Gets == '\n') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			newNode->token.type = 8;
			newNode->token.string[newNode->size] = '\0';
			count = count + 1;
		}

		/*
		Judge whether the token is alphabet
		*/
		else if ((Gets >= 'a' && Gets <= 'z') || (Gets >= 'A' && Gets <= 'Z')) {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;

		F2:Gets = fgetc(inputFile);

			if ((Gets >= 'a' && Gets <= 'z') || (Gets >= 'A' && Gets <= 'Z')) {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
				goto F2;
			}
			else if (Gets >= '0' && Gets <= '9') {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
				goto F2;
			}
			else if (Gets == EOF) {
				newNode->token.string[newNode->size] = '\0';
				newNode->token.type = 2;
				break;
			}
			else {
				fseek(inputFile, -1, SEEK_CUR);
			}

			newNode->token.string[newNode->size] = '\0';
			newNode->token.type = 2;

			/*
			Judge whether the token is Keywords
			*/
			if (strcmp(newNode->token.string, "while") == 0) {
				newNode->token.type = 1;
			}
			if (strcmp(newNode->token.string, "else") == 0) {
				newNode->token.type = 1;
			}
			if (strcmp(newNode->token.string, "if") == 0) {
				newNode->token.type = 1;
			}
			if (strcmp(newNode->token.string, "return") == 0) {
				newNode->token.type = 1;
			}
			if (strcmp(newNode->token.string, "num") == 0) {
				newNode->token.type = 1;
			}

		}

		/*
		Judge the token is number
		*/
		else if (Gets >= '0' && Gets <= '9') {

			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
		F1: Gets = fgetc(inputFile);
			if (Gets == '|') {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
				goto F1;
			}
			else if (Gets >= '0' && Gets <= '9') {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
				goto F1;
			}
			else if (Gets == EOF) {
				newNode->token.string[newNode->size] = '\0';
				newNode->token.type = 3;
				break;
			}
			else {
				fseek(inputFile, -1, SEEK_CUR);
			}
			newNode->token.string[newNode->size] = '\0';
			newNode->token.type = 3;
		}

		/*
		Judge whether the token is - or -->
		*/
		else if (Gets == '-') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			newNode->token.type = 5;
			Gets = fgetc(inputFile);
			if (Gets == '-') {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
				Gets = fgetc(inputFile);
				if (Gets == '>') {
					newNode->token.string[newNode->size] = Gets;
					newNode->size = newNode->size + 1;
					newNode->token.string[newNode->size] = '\0';
				}
				else {
					printf("Line %d error.\n", count);
				}
			}
			else if (Gets == EOF) {
				newNode->token.string[newNode->size] = '\0';
				break;
			}
			else {
				newNode->token.string[newNode->size] = '\0';
				fseek(inputFile, -1, SEEK_CUR);
			}
		}

		/*
		Judge whether the token is + * & .
		*/
		else if (Gets == '+' || Gets == '*' || Gets == '%' || Gets == '.') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			newNode->token.type = 5;

			Gets = fgetc(inputFile);
			if (Gets == EOF) {
				newNode->token.string[newNode->size] = '\0';
				break;
			}
			else {
				fseek(inputFile, -1, SEEK_CUR);
			}
			newNode->token.string[newNode->size] = '\0';
		}

		/*
		Judge whether the token is = < > ! == <= >= !=
		*/
		else if (Gets == '=' || Gets == '<' || Gets == '>' || Gets == '!') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			newNode->token.type = 5;

			Gets = fgetc(inputFile);
			if (Gets == '=') {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;

			}
			else if (Gets == EOF) {
				newNode->token.string[newNode->size] = '\0';
				break;
			}
			else {
				fseek(inputFile, -1, SEEK_CUR);
			}
			newNode->token.string[newNode->size] = '\0';

		}

		/*
		Judge whether the token is | ||
		*/
		else if (Gets == '|') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			newNode->token.type = 5;
			Gets = fgetc(inputFile);
			if (Gets == '|') {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
			}
			else if (Gets == EOF) {
				newNode->token.string[newNode->size] = '\0';
				break;
			}
			else {
				fseek(inputFile, -1, SEEK_CUR);
			}
			newNode->token.string[newNode->size] = '\0';
		}
		else if (Gets == '&') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			newNode->token.type = 5;
			Gets = fgetc(inputFile);
			if (Gets == '&') {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
			}
			else if (Gets == EOF) {
				newNode->token.string[newNode->size] = '\0';
				break;
			}
			else {
				fseek(inputFile, -1, SEEK_CUR);
			}
			newNode->token.string[newNode->size] = '\0';
		}

		/*
		Judge whether the token is ! !=
		*/
		else if (Gets == '!') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			newNode->token.type = 5;
			Gets = fgetc(inputFile);
			if (Gets == '=') {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
			}
			else if (Gets == EOF) {
				newNode->token.string[newNode->size] = '\0';
				break;
			}
			else {
				fseek(inputFile, -1, SEEK_CUR);
			}
			newNode->token.string[newNode->size] = '\0';
		}

		/*
		Judge whether the token is ( ) { } , ; [ ]
		*/
		else if (Gets == '(' || Gets == ')' || Gets == '{' || Gets == '}' || Gets == ',' || Gets == ';' || Gets == '[' || Gets == ']') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			newNode->token.type = 6;
			newNode->token.string[newNode->size] = '\0';
		}
		else if (Gets == ':') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			newNode->token.type = 6;
			Gets = fgetc(inputFile);
			if (Gets == ')') {
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
				newNode->token.string[newNode->size] = '\0';
			}
			else if (Gets == EOF) {
				newNode->token.string[newNode->size] = '\0';
				break;
			}
			else {
				fseek(inputFile, -1, SEEK_CUR);
			}
			newNode->token.string[newNode->size] = '\0';
		}

		/*
		Judge the charater is /   //      / *     * /
		*/
		else if (Gets == '/') {
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;
			Gets = fgetc(inputFile);

			if (Gets == '/') {

				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;


			F3:   Gets = fgetc(inputFile);
				if (Gets == '\n') {

					fseek(inputFile, -1, SEEK_CUR);

				}
				else if (Gets == EOF) {
					newNode->token.string[newNode->size] = '\0';
					break;
				}
				else {
					newNode->token.string[newNode->size] = Gets;
					newNode->size = newNode->size + 1;
					goto F3;
				}
				newNode->token.type = 4;
				newNode->token.string[newNode->size] = '\0';
			}
			else if (Gets == '*') {

				newNode->token.type = 4;
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;

			F4:	Gets = fgetc(inputFile);
				if (Gets == '\n') {
					count = count + 1;
				}
				if (Gets == '*') {

					newNode->token.string[newNode->size] = Gets;
					newNode->size = newNode->size + 1;
					Gets = fgetc(inputFile);

					if (Gets == '/') {

						newNode->token.string[newNode->size] = Gets;
						newNode->size = newNode->size + 1;
						newNode->token.string[newNode->size] = '\0';

					}
					else {
						goto F4;

					}
				}
				else if (Gets == EOF) {
					newNode->token.string[newNode->size] = '\0';
					break;
				}
				else {
					newNode->token.string[newNode->size] = Gets;
					newNode->size = newNode->size + 1;
					goto F4;
				}

			}
			else {

				newNode->token.type = 5;
				newNode->token.string[newNode->size] = '\0';
				fseek(inputFile, -1, SEEK_CUR);

			}
		}

		/*
		Judge whether the token is string
		*/
		else if (Gets == '\"' || Gets == '\'')
		{
			newNode->token.string[newNode->size] = Gets;
			newNode->size = newNode->size + 1;

		F5:	Gets = fgetc(inputFile);
			if (Gets == '\n')
			{

				fseek(inputFile, -1, SEEK_CUR);
				newNode->token.string[newNode->size] = '\0';

			}
			else if (Gets == '\"' || Gets == '\'')
			{
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
				newNode->token.string[newNode->size] = '\0';

			}
			else if (Gets == '\\')
			{
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;

				Gets = fgetc(inputFile);
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
				goto F5;

			}
			else if (Gets == EOF) {
				fseek(inputFile, -1, SEEK_CUR);
				newNode->token.string[newNode->size] = '\0';
			}
			else
			{
				newNode->token.string[newNode->size] = Gets;
				newNode->size = newNode->size + 1;
				goto F5;

			}
			newNode->token.type = 7;
			newNode->token.string[newNode->size] = '\0';
		}
		else if (Gets == EOF) {
			newNode->token.type = 10;
		}
		else {

			newNode->token.type = 9;
			printf("Line %d error.\n", count);
		}

		end_insert_list(head, newNode->token.string, newNode->token.type);
	}
}