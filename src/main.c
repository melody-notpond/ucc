#include <stdio.h>

#include "lexer.h"

int main() {
    Lexer lexer = ucc_new_lexer("     27   6");

    Token token = ucc_lexer_next(&lexer);
    printf("token is integer? %s\ntoken value: ", token.type == TOKEN_TYPE_INTEGER ? "true" : "false");
    for (int i = 0; i < token.length; i++) {
        putc(token.token[i], stdout);
    }
    printf("\n");

    token = ucc_lexer_next(&lexer);
    printf("token is integer? %s\ntoken value: ", token.type == TOKEN_TYPE_INTEGER ? "true" : "false");
    for (int i = 0; i < token.length; i++) {
        putc(token.token[i], stdout);
    }
    printf("\n");

    token = ucc_lexer_next(&lexer);
    printf("token is EOF? %s\n", token.type == TOKEN_TYPE_EOF ? "true" : "false");
}
