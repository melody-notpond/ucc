#include <stdbool.h>
#include <stdio.h>

#include "lexer.h"

// ucc_new_lexer(char *) -> Lexer
// Creates a new Lexer from a string.
Lexer ucc_new_lexer(char *string) {
    return (Lexer) {
        .string = string,
        .pos = 0,
    };
}

// ucc_lexer_next(Lexer *) -> Token
// Lexes the next token from the given string.
Token ucc_lexer_next(Lexer *lexer) {
    char c;
    int start = lexer->pos;
    int i = lexer->pos;
    bool stop = false;

    TokenType type = TOKEN_TYPE_INVALID;

    while (true) {
        c = lexer->string[i];
        switch (type) {
            case TOKEN_TYPE_INVALID:
                if (i != start) {
                    stop = true;
                } else if (c == '\0') {
                    type = TOKEN_TYPE_EOF;
                    stop = true;
                } else if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
                    start++;
                } else if ('0' <= c && c <= '9') {
                    type = TOKEN_TYPE_INTEGER;
                } else if (c == '*') {
                    type = TOKEN_TYPE_ASTRISK;
                } else if (c == '/') {
                    type = TOKEN_TYPE_SLASH;
                } else if (c == '%') {
                    type = TOKEN_TYPE_PERCENT;
                } else if (c == '+') {
                    type = TOKEN_TYPE_PLUS;
                } else if (c == '-') {
                    type = TOKEN_TYPE_MINUS;
                } else if (c == '(') {
                    type = TOKEN_TYPE_LPAREN;
                } else if (c == ')') {
                    type = TOKEN_TYPE_RPAREN;
                }
                break;

            case TOKEN_TYPE_INTEGER:
                if (c < '0' || c > '9') {
                    stop = true;
                }
                break;

            default:
                stop = true;
                break;
        }

        if (stop)
            break;

        i++;
    }

    lexer->pos = i;

    return (Token) {
        .token = lexer->string + start,
        .length = i - start,
        .type = type,
    };
}

// ucc_print_token(Token) -> void
// Prints out a token to stdout.
void ucc_print_token(Token token) {
    switch (token.type) {
        case TOKEN_TYPE_INVALID:
            printf("invalid");
            break;
        case TOKEN_TYPE_EOF:
            printf("eof");
            break;
        case TOKEN_TYPE_HASH:
            break;
        case TOKEN_TYPE_COMMA:
            break;
        case TOKEN_TYPE_SEMICOLON:
            break;
        case TOKEN_TYPE_LBRACE:
            break;
        case TOKEN_TYPE_RBRACE:
            break;
        case TOKEN_TYPE_LBRACK:
            break;
        case TOKEN_TYPE_RBRACK:
            break;
        case TOKEN_TYPE_LPAREN:
            printf("lparen");
            break;
        case TOKEN_TYPE_RPAREN:
            printf("rparen");
            break;
        case TOKEN_TYPE_ASTRISK:
            printf("astrisk");
            break;
        case TOKEN_TYPE_PLUS:
            printf("plus");
            break;
        case TOKEN_TYPE_MINUS:
            printf("minus");
            break;
        case TOKEN_TYPE_SLASH:
            printf("slash");
            break;
        case TOKEN_TYPE_EXCLAMATION:
            break;
        case TOKEN_TYPE_PERCENT:
            printf("percent");
            break;
        case TOKEN_TYPE_CARET:
            break;
        case TOKEN_TYPE_AMPERSAND:
            break;
        case TOKEN_TYPE_DOUBLE_AMPERSAND:
            break;
        case TOKEN_TYPE_PIPE:
            break;
        case TOKEN_TYPE_DOUBLE_PIPE:
            break;
        case TOKEN_TYPE_TILDE:
            break;
        case TOKEN_TYPE_COLON:
            break;
        case TOKEN_TYPE_DOT:
            break;
        case TOKEN_TYPE_ARROW:
            break;
        case TOKEN_TYPE_LESS_THAN:
            break;
        case TOKEN_TYPE_GREATER_THAN:
            break;
        case TOKEN_TYPE_LESS_THAN_EQUALS:
            break;
        case TOKEN_TYPE_GREATER_THAN_EQUALS:
            break;
        case TOKEN_TYPE_EQUALS:
            break;
        case TOKEN_TYPE_NOT_EQUALS:
            break;
        case TOKEN_TYPE_INCREMENT:
            break;
        case TOKEN_TYPE_DECREMENT:
            break;
        case TOKEN_TYPE_SET:
            break;
        case TOKEN_TYPE_IF:
            break;
        case TOKEN_TYPE_ELSE:
            break;
        case TOKEN_TYPE_DO:
            break;
        case TOKEN_TYPE_WHILE:
            break;
        case TOKEN_TYPE_FOR:
            break;
        case TOKEN_TYPE_SWITCH:
            break;
        case TOKEN_TYPE_CASE:
            break;
        case TOKEN_TYPE_CONTINUE:
            break;
        case TOKEN_TYPE_BREAK:
            break;
        case TOKEN_TYPE_RETURN:
            break;
        case TOKEN_TYPE_STRUCT:
            break;
        case TOKEN_TYPE_ENUM:
            break;
        case TOKEN_TYPE_UNION:
            break;
        case TOKEN_TYPE_TYPEDEF:
            break;
        case TOKEN_TYPE_UNSIGNED:
            break;
        case TOKEN_TYPE_LONG:
            break;
        case TOKEN_TYPE_SHORT:
            break;
        case TOKEN_TYPE_INT:
            break;
        case TOKEN_TYPE_CHAR:
            break;
        case TOKEN_TYPE_BOOL:
            break;
        case TOKEN_TYPE_SYMBOL:
            break;
        case TOKEN_TYPE_INTEGER:
            printf("integer");
            break;
        case TOKEN_TYPE_CHARACTER:
            break;
        case TOKEN_TYPE_STRING:
            break;
    }

    printf(" ");

    for (int i = 0; i < token.length; i++) {
        printf("%c", token.token[i]);
    }
}
