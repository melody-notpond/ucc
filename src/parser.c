#include <stdio.h>
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

static ParseResult parse_value(Lexer *lexer);
static ParseResult parse_mul(Lexer *lexer);
static ParseResult parse_add(Lexer *lexer);
//static ParseResult parse_bitshift(Lexer *lexer);
//static ParseResult parse_bitwise_and(Lexer *lexer);
//static ParseResult parse_bitwise_or(Lexer *lexer);
//static ParseResult parse_bitwise_xor(Lexer *lexer);
//static ParseResult parse_logical_or(Lexer *lexer);
//static ParseResult parse_logical_or(Lexer *lexer);

#define unwrap(v, acc)                                   \
    ({                                              \
        ParseResult unwrap = (v);                   \
        if (!unwrap.success) {                      \
            ucc_clean_ast(acc);                     \
            return unwrap;                          \
        }                                           \
        unwrap.value.ast;                           \
    })

static ParseResult parse_value(Lexer *lexer) {
    Token t;

    if ((t = consume_token(lexer, TOKEN_TYPE_INTEGER)).type != TOKEN_TYPE_INVALID) {
        return (ParseResult) {
            .success = true,
            .value.ast = {
                .token = t,
                .children = NULL,
                .length = 0,
                .cap = 0,
            },
        };
    } else if ((t = consume_token(lexer, TOKEN_TYPE_LPAREN)).type != TOKEN_TYPE_INVALID) {
        Ast inner = unwrap(parse_add(lexer), NULL);
        if ((t = consume_token(lexer, TOKEN_TYPE_RPAREN)).type != TOKEN_TYPE_INVALID) {
            return (ParseResult) {
                .success = true,
                .value.ast = inner,
            };
        } else {
            return (ParseResult) {
                .success = false,
                .value.error_message = "Expected right parenthesis",
            };
        }
    } else {
        return (ParseResult) {
            .success = false,
            .value.error_message = "Expected integer or parenthesised expression",
        };
    }
}

static ParseResult parse_mul(Lexer *lexer) {
    Ast top = unwrap(parse_value(lexer), NULL);

    Token op;
    while (
           (op = consume_token(lexer, TOKEN_TYPE_ASTRISK)).type != TOKEN_TYPE_INVALID
        || (op = consume_token(lexer, TOKEN_TYPE_SLASH)).type != TOKEN_TYPE_INVALID
        || (op = consume_token(lexer, TOKEN_TYPE_PERCENT)).type != TOKEN_TYPE_INVALID
    ) {
        Ast next = (Ast) {
            .token = op,
            .children = calloc(2, sizeof(Ast)),
            .length = 1,
            .cap = 2,
        };
        next.children[0] = top;
        next.children[next.length++] = unwrap(parse_value(lexer), &next);
        top = next;
    }

    return (ParseResult) {
        .success = true,
        .value.ast = top,
    };
}

static ParseResult parse_add(Lexer *lexer) {
    Ast top = unwrap(parse_mul(lexer), NULL);

    Token op;
    while (
           (op = consume_token(lexer, TOKEN_TYPE_PLUS)).type != TOKEN_TYPE_INVALID
        || (op = consume_token(lexer, TOKEN_TYPE_MINUS)).type != TOKEN_TYPE_INVALID
    ) {
        Ast next = (Ast) {
            .token = op,
            .children = calloc(2, sizeof(Ast)),
            .length = 1,
            .cap = 2,
        };
        next.children[0] = top;
        next.children[next.length++] = unwrap(parse_mul(lexer), &next);
        top = next;
    }

    return (ParseResult) {
        .success = true,
        .value.ast = top,
    };
}

// ucc_parser_parse(char *) -> ParseResult
// Parses a string into an abstract syntax tree. Returns an error message on failure.
ParseResult ucc_parser_parse(char *string) {
    Lexer lexer = ucc_new_lexer(string);
    Ast ast = unwrap(parse_add(&lexer), NULL);
    if (consume_token(&lexer, TOKEN_TYPE_EOF).type != TOKEN_TYPE_INVALID) {
        return (ParseResult) {
            .success = true,
            .value.ast = ast,
        };
    } else {
        ucc_clean_ast(&ast);
        return (ParseResult) {
            .success = false,
            .value.error_message = "Expected EOF",
        };
    }
}

static void print_ast_helper(Ast *ast, int indent) {
    for (int i = 0; i < indent; i++) {
        printf("    ");
    }

    ucc_print_token(ast->token);
    printf("\n");

    for (int i = 0; i < ast->length; i++) {
        print_ast_helper(ast->children + i, indent + 1);
    }
}

// ucc_print_ast(Ast *) -> void
// Prints out an ast.
void ucc_print_ast(Ast *ast) {
    print_ast_helper(ast, 0);
}

// ucc_clean_ast(Ast *) -> void
// Cleans up an Ast node and its children.
void ucc_clean_ast(Ast *ast) {
    if (ast == NULL)
        return;

    for (int i = 0; i < ast->length; i++) {
        ucc_clean_ast(ast->children + i);
    }
    free(ast->children);
}
