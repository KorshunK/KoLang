#include "parser.h"
#include <stdlib.h>
#include <string.h>

static void parser_advance(Parser* p) {
    p->current = next_token(p->lexer);
}

void parser_init(Parser* p, Lexer* lexer) {
    p->lexer = lexer;
    parser_advance(p);
}

ASTNode* parse_statement(Parser* p);

ASTNode* parse_print(Parser* p) {
    char* func_name = strdup(p->current.lexeme);
    parser_advance(p);

    ASTNode* str_arg = NULL;
    if (p->current.type == TOKEN_STRING) {
        str_arg = malloc(sizeof(ASTNode));
        str_arg->kind = AST_STRING_LITERAL;
        str_arg->string_literal = strdup(p->current.lexeme);
        parser_advance(p);
    }

    ASTNode* call = malloc(sizeof(ASTNode));
    call->kind = AST_CALL;
    call->call_expr.callee = func_name;
    call->call_expr.argc = (str_arg ? 1 : 0);
    call->call_expr.args = str_arg ? malloc(sizeof(ASTNode*)) : NULL;
    if (str_arg) call->call_expr.args[0] = str_arg;
    return call;
}

ASTNode* parse_statement(Parser* p) {
    if (p->current.type == TOKEN_PRINT) {
        return parse_print(p);
    }
    return NULL;
}

ASTNode* parse_program(Parser* p) {
    if (p->current.type == TOKEN_PUBLIC) {
        parser_advance(p);
        if (p->current.type == TOKEN_FUNCTION) {
            parser_advance(p);
            if (p->current.type == TOKEN_IDENTIFIER && strcmp(p->current.lexeme, "main") == 0) {
                parser_advance(p);
                if (p->current.type == TOKEN_LPAREN) parser_advance(p);
                if (p->current.type == TOKEN_RPAREN) parser_advance(p);
                if (p->current.type == TOKEN_LBRACE) parser_advance(p);

                ASTNode* body = parse_statement(p);

                if (p->current.type == TOKEN_RBRACE) parser_advance(p);

                ASTNode* func = malloc(sizeof(ASTNode));
                func->kind = AST_FUNCTION;
                func->function_def.name = strdup("main");
                func->function_def.body = body;
                return func;
            }
        }
    }
    return NULL;
}
