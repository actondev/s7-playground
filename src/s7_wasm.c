#include "s7.h"

#include <stdio.h>

s7_scheme* g_sc = NULL;
s7_pointer g_out, g_err;

int main() {
    printf("hello, world!\n");
    g_sc = s7_init();

    return 0;
}

// exported to wasm
const char* eval_string(char* str) {
     // closing.. without having opened?
     // seems to be ok
     s7_close_output_port(g_sc, g_out);
     s7_close_output_port(g_sc, g_err);

     // stdout
     g_out = s7_open_output_string(g_sc);
     s7_set_current_output_port(g_sc, g_out);

     // stderr
     g_err = s7_open_output_string(g_sc);
     s7_set_current_error_port(g_sc, g_err);

     s7_pointer result = s7_eval_c_string(g_sc, str);
     return s7_object_to_c_string(g_sc, result);
}

const char* get_out(){
     return s7_get_output_string(g_sc, s7_current_output_port(g_sc));
}

const char* get_err(){
     return s7_get_output_string(g_sc, s7_current_error_port(g_sc));
}
