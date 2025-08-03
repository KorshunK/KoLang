#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,

    // Keywords
    TOKEN_LET,
    TOKEN_FUNCTION,
    TOKEN_PUBLIC,
    TOKEN_PRIVATE,
    TOKEN_PROTECTED,
    TOKEN_RETURN,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_PRINT,
    TOKEN_INPUT,

    // Types
    TOKEN_TYPE_INT,
    TOKEN_TYPE_FLOAT,
    TOKEN_TYPE_BOOL,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_VOID,

    // Symbols and operators
    TOKEN_PLUS,       // +
    TOKEN_MINUS,      // -
    TOKEN_STAR,       // *
    TOKEN_SLASH,      // /
    TOKEN_EQUAL, 
    TOKEN_NOT_EQUAL,     // =
    TOKEN_COLON,      // :
    TOKEN_SEMICOLON,  // ;
    TOKEN_LPAREN,     // (
    TOKEN_RPAREN,     // )
    TOKEN_LBRACE,     // {
    TOKEN_RBRACE,     // }
    TOKEN_COMMA,       // ,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
    int line;
} Token;

typedef struct {
    const char* src;
    int pos;
    int line;
} Lexer;

void init_lexer(Lexer* lexer, const char* src);
Token next_token(Lexer* lexer);
void free_lexer();

#endif