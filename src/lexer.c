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

