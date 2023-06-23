

/*
Define some enum for give the token type
*/
enum TYPE { KEYWORD = 1, ID, NUM, NOTE, OPERATOR, SEPERATOR, STRING, ENTER, ERROR, ENDOFFLIE };

/*
Define the token content
*/
typedef struct Token {
	char string[100];
	int type;
}Token;

/*
Define a Node
*/
typedef struct Node
{
	Token token;
	int size;
	struct Node* PreNode;
	struct Node* NextNode;
}Node;
