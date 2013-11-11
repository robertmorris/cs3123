#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

// CS3123Project1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <process.h>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <ostream>

using namespace std;

int charClass;
char lexeme [100];
char alphas [100];
char numbers [100];
char others [100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE * pFile;


void addChar();
void getChar();
void getNonBlank();
int lex();

#define LETTER 0
#define DIGIT 1
#define UNKOWN 99

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

int _tmain(int argc, _TCHAR* argv[])
{

	fopen_s(&pFile, "Text.txt", "r");
	if(pFile == NULL)
		perror("ERROR - cannot open file \n");
	else {
		getChar();
		do {
			lex();
		}while (nextToken != EOF);
	}

	system("pause");
}

int lookup(char ch) {
	switch (ch) {
	case '(':
		addChar();
		nextToken = LEFT_PAREN;
		break;

		case ')':
		addChar();
		nextToken = RIGHT_PAREN;
		break;

		case '+':
		addChar();
		nextToken = ADD_OP;
		break;

		case '-':
		addChar();
		nextToken = SUB_OP;
		break;

		case '*':
		addChar();
		nextToken = MULT_OP;
		break;

		case '/':
		addChar();
		nextToken = DIV_OP;
		break;

		default:
			addChar();
			nextToken = EOF;
			break;
	}
	return nextToken;
}

void addChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}

void getChar(){
	if((nextChar = fgetc(pFile)) != EOF){
		if(isalpha(nextChar))
			charClass = LETTER;
	else if(isdigit(nextChar))
		charClass = DIGIT;
	else 
		charClass = UNKOWN;
	}
	else
		charClass = EOF;
}

void getNonBlank() {
	while (isspace(nextChar))
		getChar();
}

int lex(){
	lexLen = 0;
	getNonBlank();
	switch (charClass) {

	case LETTER:
		addChar();
		getChar();
		while (charClass == LETTER || charClass == DIGIT) {
			addChar();
			getChar();
		}
		nextToken = IDENT;
		break;

	case DIGIT:
		addChar();
		getChar();
		while (charClass == DIGIT) {
			addChar();
			getChar();
		}
		nextToken = INT_LIT;
		break;

	case UNKOWN:
		lookup(nextChar);
		getChar();
		break;

	case EOF:
		nextToken = EOF;
		lexeme[0] = 'E';
		lexeme[1] = 'O';
		lexeme[2] = 'F';
		lexeme[3] = 0;
		break;
	}

	printf("next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
	return nextToken;
}