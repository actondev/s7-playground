#include "s7.h"

#include <stdio.h>

void _s7_print_stderr(s7_scheme *sc, uint8_t c, s7_pointer port) {
    printf("%c", c);
}

int main() {
  printf("hello, world!\n");
  s7_scheme* sc = s7_init();
  s7_set_current_output_port(sc, s7_open_output_function(sc, _s7_print_stderr));
  s7_eval_c_string(sc, "(format #t \"result is ~A\n\" (+ 1 2 3))");
  return 0;
}
