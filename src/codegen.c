#include "codegen.h"

static void compile_ast_node(FILE *file, Ast ast) {
    switch (ast.token.type) {
        case TOKEN_TYPE_INTEGER:
            fprintf(file, "    IMM r1 ");
            for (int i = 0; i < ast.token.length; i++) {
                fprintf(file, "%c", ast.token.token[i]);
            }
            fprintf(file, "\n");
            break;

        default:
            fprintf(file, "    ; unknown token type %i\n", ast.token.type);
            break;
    }
}

// ucc_compile_ast_to_urcl(FILE *, Ast, UrclSettings) -> void
// Compiles an abstract syntax tree into URCL.
void ucc_compile_ast_to_urcl(FILE *file, Ast ast, UrclSettings settings) {
    if (settings.min_bitwidth != 0) {
        fprintf(file, "BITS >= %i\n", settings.exact_bitwidth);
    } else if (settings.exact_bitwidth != 0) {
        fprintf(file, "BITS == %i\n", settings.exact_bitwidth);
    } else if (settings.max_bitwidth != 0) {
        fprintf(file, "BITS <= %i\n", settings.exact_bitwidth);
    } else {
        fprintf(file, "BITS == 8\n");
    }

    if (settings.min_reg_count != 0) {
        fprintf(file, "MINREG %i\n", settings.min_reg_count);
    } else {
        fprintf(file, "MINREG 8\n");
    }

    if (settings.min_heap_size != 0) {
        fprintf(file, "MINHEAP %i\n", settings.min_heap_size);
    } else {
        fprintf(file, "MINHEAP 16\n");
    }

    fprintf(file, "RUN %s\n", settings.on_ram ? "RAM" : "ROM");

    if (settings.min_stack != 0) {
        fprintf(file, "MINSTACK %i\n", settings.min_stack);
    } else {
        fprintf(file, "MINSTACK 8\n");
    }

    fprintf(file, "\n");
    compile_ast_node(file, ast);
}

