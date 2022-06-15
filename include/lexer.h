#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_TYPE_INVALID,
    TOKEN_TYPE_EOF,

    TOKEN_TYPE_HASH,

    TOKEN_TYPE_COMMA,
    TOKEN_TYPE_SEMICOLON,

    TOKEN_TYPE_LBRACE,
    TOKEN_TYPE_RBRACE,
    TOKEN_TYPE_LBRACK,
    TOKEN_TYPE_RBRACK,
    TOKEN_TYPE_LPAREN,
    TOKEN_TYPE_RPAREN,

    TOKEN_TYPE_ASTRISK,
    TOKEN_TYPE_PLUS,
    TOKEN_TYPE_MINUS,
    TOKEN_TYPE_SLASH,
    TOKEN_TYPE_EXCLAMATION,
    TOKEN_TYPE_PERCENT,
    TOKEN_TYPE_CARET,
    TOKEN_TYPE_AMPERSAND,
    TOKEN_TYPE_DOUBLE_AMPERSAND,
    TOKEN_TYPE_PIPE,
    TOKEN_TYPE_DOUBLE_PIPE,
    TOKEN_TYPE_TILDE,
    TOKEN_TYPE_COLON,

    TOKEN_TYPE_DOT,
    TOKEN_TYPE_ARROW,

    TOKEN_TYPE_LESS_THAN,
    TOKEN_TYPE_GREATER_THAN,
    TOKEN_TYPE_LESS_THAN_EQUALS,
    TOKEN_TYPE_GREATER_THAN_EQUALS,
    TOKEN_TYPE_EQUALS,
    TOKEN_TYPE_NOT_EQUALS,

    TOKEN_TYPE_INCREMENT,
    TOKEN_TYPE_DECREMENT,

    TOKEN_TYPE_SET,

    TOKEN_TYPE_IF,
    TOKEN_TYPE_ELSE,
    TOKEN_TYPE_DO,
    TOKEN_TYPE_WHILE,
    TOKEN_TYPE_FOR,
    TOKEN_TYPE_SWITCH,
    TOKEN_TYPE_CASE,

    TOKEN_TYPE_CONTINUE,
    TOKEN_TYPE_BREAK,
    TOKEN_TYPE_RETURN,

    TOKEN_TYPE_STRUCT,
    TOKEN_TYPE_ENUM,
    TOKEN_TYPE_UNION,
    TOKEN_TYPE_TYPEDEF,

    TOKEN_TYPE_UNSIGNED,
    TOKEN_TYPE_LONG,
    TOKEN_TYPE_INT,
    TOKEN_TYPE_SHORT,
    TOKEN_TYPE_CHAR,
    TOKEN_TYPE_BOOL,

    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_INTEGER,
    TOKEN_TYPE_CHARACTER,
    TOKEN_TYPE_STRING,
} TokenType;

typedef struct {
    char *token;
    int length;
    TokenType type;
} Token;

typedef struct {
    char *string;
    int pos;
} Lexer;

// ucc_new_lexer(char *) -> Lexer
// Creates a new Lexer from a string.
Lexer ucc_new_lexer(char *string);

// ucc_lexer_next(Lexer *) -> Token
// Lexes the next token from the given string.
Token ucc_lexer_next(Lexer *lexer);

// ucc_print_token(Token) -> void
// Prints out a token to stdout.
void ucc_print_token(Token token);

#endif /* LEXER_H */
