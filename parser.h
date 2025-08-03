#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct ASTNode {
    enum { AST_CALL, AST_STRING_LITERAL, AST_FUNCTION } kind;
    union {
        struct {
            char* callee;
            struct ASTNode** args;
            int argc;
        } call_expr;
        char* string_literal;
        struct {
            char* name;
            struct ASTNode* body;
        } function_def;
    };
} ASTNode;

typedef struct {
    Lexer* lexer;
    Token current;
} Parser;

void parser_init(Parser* p, Lexer* lexer);
ASTNode* parse_program(Parser* p);

#endif
