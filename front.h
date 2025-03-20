#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define MISC 2
#define UNKNOWN 99

/* Token codes */
#define END_OF_FILE "EOF"
#define INT_LIT "INT_LIT"
#define IDENT "IDENT"
#define ASSIGN_OP "ASSIGN_OP"
#define ADD_OP "ADD_OP"
#define SUB_OP "SUB_OP"
#define MULT_OP "MULT_OP"
#define DIV_OP "DIV_OP"
#define OPEN_PAREN "OPEN_PAREN"
#define CLOSE_PAREN "CLOSE_PAREN"
#define LESSER_OP "LESSER_OP"
#define GREATER_OP "GREATER_OP"
#define EQUAL_OP "EQUAL_OP"
#define NEQUAL_OP "NEQUAL_OP"
#define LEQUAL_OP "LEQUAL_OP"
#define GEQUAL_OP "GEQUAL_OP"
#define MOD_OP "MOD_OP"
#define BOOL_AND "BOOL_AND"
#define BOOL_OR "BOOL_OR"
#define BOOL_NOT "BOOL_NOT"
#define SEMICOLON "SEMICOLON"
#define KEY_IN "KEY_IN"
#define KEY_OUT "KEY_OUT"
#define KEY_IF "KEY_IF"
#define KEY_ELSE "KEY_ELSE"
#define OPEN_CURL "OPEN_CURL"
#define CLOSE_CURL "CLOSE_CURL"
#define OTHER "UNKNOWN"


char* lex();

#endif
