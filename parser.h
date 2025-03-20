#ifndef PARSER_H
#define PARSER_H

//parser functions
void stmt();
void stmtp();
void conditional();
void conditionalp();
void conditional2p();
void expr();
void exprp();
void term();
void termp();
void factor();
void variable();

//variables shared between parser and front
extern char* nextToken;
extern int lineNum;
extern char lexeme[];
#endif
