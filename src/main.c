#include <stdio.h>

#include "parser.h"

int main() {
    ParseResult result = ucc_parser_parse("   69   ");
    if (result.success) {
        printf("success!\n");
    } else {
        printf("error parsing string: %s\n", result.value.error_message);
    }
}
