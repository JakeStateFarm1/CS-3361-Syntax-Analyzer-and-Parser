/*
Parser.C
Parses through a user submitted file and checks if it fits the rules of the cooke programming language.
Jake Boles R11805778
11/20/24
Version 1.00
This program is not designed to run on its own, its dependent on the front.c program, as well as the front.h and parser.h header files.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "front.h"

static void error(int n){
    printf("Error encounter on line %d:  The next lexeme was %s and the next token was %s",lineNum,lexeme,nextToken);
    exit(1);
}
void stmt(){ //implements the s rules
    if(strcmp(nextToken,IDENT)==0) //checks the V=E case
    {
        variable();
        if(strcmp(nextToken,ASSIGN_OP)==0){
            lex();
            expr();
            if(strcmp(nextToken,SEMICOLON)==0){
                lex();
                stmtp();
            }
            else error(1);
        } else error(2);
    } else if(strcmp(nextToken,KEY_IN)==0){ //checks the input(V) case
        lex();
        if(strcmp(nextToken,OPEN_PAREN)==0){
            lex();
            variable();
            if(strcmp(nextToken,CLOSE_PAREN)==0){
                lex();
                if(strcmp(nextToken,SEMICOLON)==0){
                    lex();
                    stmtp();
                }
                else error(3);
            }
            else error(4);
        }
        else error(5);
    } else if(strcmp(nextToken,KEY_OUT)==0){ //checks the output(E) case
        lex();
        if(strcmp(nextToken,OPEN_PAREN)==0){
            lex();
            expr();
            if(strcmp(nextToken,CLOSE_PAREN)==0){
                lex();
                if(strcmp(nextToken,SEMICOLON)==0){
                    lex();
                    stmtp();
                }
                else error(6);
            }
            else error(7);
        }
        else error(8);
    } else if (strcmp(nextToken,KEY_IF)==0){ //checks the if and if else case
        lex();
        if(strcmp(nextToken,OPEN_PAREN)==0){
            lex();
            conditional();
            if(strcmp(nextToken,CLOSE_PAREN)==0){
                lex();
                if(strcmp(nextToken,OPEN_CURL)==0){
                    lex();
                    stmt();
                    if(strcmp(nextToken,CLOSE_CURL)==0){
                        lex();
                        if(strcmp(nextToken,KEY_ELSE)==0){ //if else case
                            lex();
                            if(strcmp(nextToken,OPEN_CURL)==0){
                                lex();
                                stmt();
                                if(strcmp(nextToken,CLOSE_CURL)==0){
                                    lex();
                                    stmtp();
                                } else error(10);
                            } else error(11);
                        }
                        else{ //just if case
                            stmtp();
                        }
                    } else error(12);
                } else error(13);
            } else error(14);
        } else error(15);
    } 
    else error(16);
    
}
void stmtp(){ //subset of s, added to avoid left recursion
    if(strcmp(nextToken,IDENT)==0||strcmp(nextToken,KEY_IN)==0||strcmp(nextToken,KEY_OUT)==0||strcmp(nextToken,KEY_IF)==0){ //checks whether the next token is a valid value of s. if not, stops recursion. 
        stmt();
        stmtp();
    }
}
void conditional(){  //implents c rules, is spilt into 3 functions to avoid left recursion
    conditional2p();
    conditionalp();
}
void conditionalp(){ //subset of c designed to handle the C&&C and the C||C rules
    if(strcmp(nextToken,BOOL_AND)==0||strcmp(nextToken,BOOL_OR)==0){
        lex();
        conditional2p();
        conditionalp();
    }
}
void conditional2p(){ //subset of c designed to handle !C and all the e conditionals
    if(strcmp(nextToken,BOOL_NOT)==0){
        lex();
        conditional();
    }
    else{
        expr();
        if(strcmp(nextToken,LESSER_OP)==0||strcmp(nextToken,GREATER_OP)==0||strcmp(nextToken,EQUAL_OP)==0||strcmp(nextToken,NEQUAL_OP)==0||strcmp(nextToken,LEQUAL_OP)==0||strcmp(nextToken,GEQUAL_OP)==0){
            lex();
            expr();
        } else error(17);
        
    }

}
void expr(){ //implements the e rules
    term();
    exprp();
}
void exprp(){ //subset of e, added to the language to avoid left recursion
     if(strcmp(nextToken,ADD_OP)==0||strcmp(nextToken,SUB_OP)==0){ //checks whether the next token is a valid value of e. if not, stops recursion. 
            lex();
            term();
            exprp();
        }
}
void term(){ //implements the t rules
    factor();
    termp();
}
void termp(){ //subset of t, added to the language to avoid left recursion
     if(strcmp(nextToken,MULT_OP)==0||strcmp(nextToken,DIV_OP)==0||strcmp(nextToken,MOD_OP)==0){ //checks whether the next token is a valid value of t. if not, stops recursion. 
            lex();
            factor();
            termp();
        }
}
void factor(){ //implements the f Rules
    if(strcmp(nextToken,OPEN_PAREN)==0){ 
        lex();
        expr();
        if(strcmp(nextToken,CLOSE_PAREN)==0){
            lex();
        } else error(18);
    } else if(strcmp(nextToken,IDENT)==0){ 
        variable();
    } else if(strcmp(nextToken,INT_LIT)==0){ //implements rule N
        lex(); //since N is only used in the language here at the very end, theres no reason to create a seperate function for it. 
    } else error(19);
}
void variable(){ //implements the v rules
    if(strcmp(nextToken,IDENT)==0){ 
        lex();
    } else error(20);
}
