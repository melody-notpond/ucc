#include <stdlib.h>

#include "parser.h"

static Token consume_token(Lexer *lexer, TokenType type) {
    Lexer last = *lexer;
    Token token = ucc_lexer_next(lexer);
    if (token.type != type) {
        *lexer = last;
        return (Token) {
            .token = token.token,
            .length = 0,
            .type = TOKEN_TYPE_INVALID,
        };
    }
    return token;
}

// ucc_parser_parse(char *) -> ParseResult
// Parses a string into an abstract syntax tree. Returns an error message on failure.
ParseResult ucc_parser_parse(char *string) {
    Lexer lexer = ucc_new_lexer(string);
    Token integer = consume_token(&lexer, TOKEN_TYPE_INTEGER);
    if (integer.type == TOKEN_TYPE_INVALID) {
        return (ParseResult) {
            .success = false,
            .value.error_message = "Expected integer",
        };
    }

    Token eof = consume_token(&lexer, TOKEN_TYPE_EOF);
    if (eof.type == TOKEN_TYPE_INVALID) {
        return (ParseResult) {
            .success = false,
            .value.error_message = "Expected EOF",
        };
    }

    return (ParseResult) {
        .success = true,
        .value.ast = {
            .token = integer,
            .children = NULL,
            .length = 0,
            .cap = 0,
        },
    };
}
