#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#include "lexer.h"

typedef struct _Ast {
    Token token;

    int length;
    int cap;
    struct _Ast *children;
} Ast;

typedef struct {
    bool success;

    union {
        Ast ast;
        char* error_message;
    } value;
} ParseResult;

// ucc_parser_parse(char *) -> ParseResult
// Parses a string into an abstract syntax tree. Returns an error message on failure.
ParseResult ucc_parser_parse(char *string);

#endif /* PARSER_H */
