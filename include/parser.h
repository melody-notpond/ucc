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

// ucc_print_ast(Ast *) -> void
// Prints out an ast.
void ucc_print_ast(Ast *ast);

// ucc_clean_ast(Ast *) -> void
// Cleans up an Ast node and its children.
void ucc_clean_ast(Ast *ast);

#endif /* PARSER_H */
