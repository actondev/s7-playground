#include "s7.h"

#include <stdio.h>

void _s7_print_stdout(s7_scheme *sc, uint8_t c, s7_pointer port) {
    printf("%c", c);
}

s7_scheme* g_sc = NULL;

int main() {
    printf("hello, world!\n");
    g_sc = s7_init();
    s7_set_current_output_port(g_sc, s7_open_output_function(g_sc, _s7_print_stdout));
    s7_eval_c_string(g_sc, "(format #t \"result is ~A\n\" (+ 1 2 3))");
    return 0;
}

// exported to wasm
void eval_string(char* str) {
    printf("called eval string with arg %s\n", str);
    s7_eval_c_string(g_sc, str);
}
