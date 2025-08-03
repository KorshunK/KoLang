#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static Lexer lexer;

void init_lexer(Lexer* l, const char* src) {
    lexer.src = src;
    lexer.pos = 0;
    lexer.line = 1;
}

void free_lexer() {}

static char peek() {
    return lexer.src[lexer.pos];
}

static char advance() {
    char c = lexer.src[lexer.pos++];
    if (c == '\n') lexer.line++;
    return c;
}

static int is_keyword(const char* s) {
    if (strcmp(s, "print") == 0) return TOKEN_PRINT;
    if (strcmp(s, "input") == 0) return TOKEN_INPUT;
    if (strcmp(s, "function") == 0) return TOKEN_FUNCTION;
    if (strcmp(s, "public") == 0) return TOKEN_PUBLIC;
    return -1;
}

Token next_token(Lexer* l) {
    (void)l;
    while (isspace(peek())) advance();

    if (peek() == '\0') return (Token){TOKEN_EOF, NULL, lexer.line};

    char c = peek();
    if (c == '(') { advance(); return (Token){TOKEN_LPAREN, NULL, lexer.line}; }
    if (c == ')') { advance(); return (Token){TOKEN_RPAREN, NULL, lexer.line}; }
    if (c == '{') { advance(); return (Token){TOKEN_LBRACE, NULL, lexer.line}; }
    if (c == '}') { advance(); return (Token){TOKEN_RBRACE, NULL, lexer.line}; }

    if (c == '"') {
        advance();
        int start = lexer.pos;
        while (peek() && peek() != '"') advance();
        int len = lexer.pos - start;
        char* str = malloc(len + 1);
        memcpy(str, &lexer.src[start], len);
        str[len] = '\0';
        if (peek() == '"') advance();
        return (Token){TOKEN_STRING, str, lexer.line};
    }

    if (isalpha(c)) {
        int start = lexer.pos;
        while (isalnum(peek())) advance();
        int len = lexer.pos - start;
        char* str = malloc(len + 1);
        memcpy(str, &lexer.src[start], len);
        str[len] = '\0';
        int kw = is_keyword(str);
        if (kw != -1) return (Token){(TokenType)kw, str, lexer.line};
        return (Token){TOKEN_IDENTIFIER, str, lexer.line};
    }

    advance();
    return (Token){TOKEN_UNKNOWN, NULL, lexer.line};
}
