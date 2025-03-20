/*
Front.C
Reads through a user provided file and converts it into lexemes that a parser can understand.
Jake Boles R11805778
11/20/24
Version 1.00
This program is not designed to run on its own, its dependent on the parser.c program, as well as the front.h and parser.h header files. The program requires a text file input to run.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "front.h"
#include "parser.h"

/* Global Variable */
char lexeme [100];
char* nextToken;
int lineNum =0;
/* Local Variables */
int isEOF = 0;
static int charClass;
static char nextChar;
static int lexLen;
static FILE *in_fp;
int locallineNum=1;
/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();

/******************************************************/
/* main driver */
int main(int argc, char *argv[]) 
{
    
    if(argc<2){
        printf("ERROR- No file path provided\n");
        exit(2);
    }
    /* Open the input data file and process its contents */
    else if ((in_fp = fopen(argv[1], "r")) == NULL) {
        printf("ERROR- Your file does not exist \n");
        exit(3);
    }
     else {
        printf("Cooke Parser :: R11805778\n\n");
        getChar();
        while (isEOF == 0){
            lex();
            stmt();
        } 
    }

    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * token */
static char* lookup(char ch) {
    switch (ch) {
        case '=':
            addChar();
            if ((nextChar = getc(in_fp)) == '=') {  
                addChar();  
                nextToken = EQUAL_OP;  
            } else {
                ungetc(nextChar, in_fp);  
                nextToken = ASSIGN_OP;  
            }
            break;
        case '<':
            addChar();
            if ((nextChar = getc(in_fp)) == '=') {  
                addChar();  
                nextToken = LEQUAL_OP;  
            } else {
                ungetc(nextChar, in_fp);  
                nextToken = LESSER_OP;  
            }
            break;
        case '>':
            addChar();
            if ((nextChar = getc(in_fp)) == '=') {  
                addChar();  
                nextToken = GEQUAL_OP;  
            } else {
                ungetc(nextChar, in_fp);  
                nextToken = GREATER_OP;  
            }
            break;
        case '!':
            addChar();
            if ((nextChar = getc(in_fp)) == '=') {  
                addChar();  
                nextToken = NEQUAL_OP;  
            } else {
                ungetc(nextChar, in_fp);  
                nextToken = BOOL_NOT;  
            }
            break;
        case '(':
            addChar();
            nextToken = OPEN_PAREN;
            break;
        case ')':
            addChar();
            nextToken = CLOSE_PAREN;
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
        case '%':
            addChar();
            nextToken = MOD_OP;
            break;
        case '&':
            addChar();
            if ((nextChar = getc(in_fp)) == '&') {  
                addChar();  
                nextToken = BOOL_AND;  
            } else {
                ungetc(nextChar, in_fp);  
                nextToken = OTHER;  
            }
            break;
        case '|':
            addChar();
            if ((nextChar = getc(in_fp)) == '|') {  
                addChar();  
                nextToken = BOOL_OR;  
            } else {
                ungetc(nextChar, in_fp);  
                nextToken = OTHER;  
            }
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case '{':
            addChar();
            nextToken = OPEN_CURL;
            break;
        case '}':
            addChar();
            nextToken = CLOSE_CURL;
            break;
        default:
            addChar();
            nextToken = OTHER;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */

static void getChar() {
    nextChar = getc(in_fp);
    if (nextChar != EOF) {
        if(nextChar=='\n')
            locallineNum++;
        if (isalpha(nextChar)) 
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = MISC;
        isEOF = 1;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
char* lex() {
    lineNum = locallineNum;
    lexLen = 0;                     
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            if(strcmp(lexeme, "input") == 0) {
                nextToken = KEY_IN;
            } else if(strcmp(lexeme, "output") == 0){
                nextToken = KEY_OUT;
            } else if (strcmp(lexeme, "if") == 0) {
                nextToken = KEY_IF;
            } else if (strcmp(lexeme, "else") == 0) {
                nextToken = KEY_ELSE;
            } else if (strcmp(lexeme, "V") == 0) {
                nextToken = IDENT;
            } else if (strcmp(lexeme, "N") == 0) {
                nextToken = INT_LIT;
            } else {
                nextToken = IDENT;
            }
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        /* EOF */
        case MISC:
            nextToken = END_OF_FILE;
            isEOF=1;
            break;
        
    } /* End of switch */
    if(strcmp(nextToken,END_OF_FILE)==0){
        printf("Syntax Validated");
        exit(0);
    } 
    return nextToken;
} /* End of function lex */

