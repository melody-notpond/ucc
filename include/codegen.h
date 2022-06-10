#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdbool.h>
#include <stdio.h>

#include "parser.h"

typedef struct {
    int min_bitwidth;
    int max_bitwidth;
    int exact_bitwidth;

    int min_reg_count;
    int min_heap_size;
    bool on_ram;
    int min_stack;
} UrclSettings;

// ucc_compile_ast_to_urcl(FILE *, Ast, UrclSettings) -> void
// Compiles an abstract syntax tree into URCL.
void ucc_compile_ast_to_urcl(FILE *file, Ast ast, UrclSettings settings);

#endif /* CODEGEN_H */
