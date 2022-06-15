#include <stdio.h>

#include "parser.h"
#include "codegen.h"

int main() {
    ParseResult result = ucc_parser_parse("   69+ 2*   (3-4)   ");
    if (!result.success) {
        printf("error parsing string: %s\n", result.value.error_message);
        return 1;
    }

    Ast ast = result.value.ast;
    ucc_print_ast(&ast);
    FILE *output = fopen("a.out", "wt");
    ucc_compile_ast_to_urcl(output, ast, (UrclSettings) {
        .exact_bitwidth = 8,
    });
    fclose(output);
}
