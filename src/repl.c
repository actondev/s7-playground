#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "s7.h"

/**
 * A special REPL that (upon complete input forms) prints out a scheme list:
 * (result output error)
 *
 * This is to be parsed from emacs and fill out the s7 document results
 */
int main(int argc, char** argv)
{
    s7_scheme* sc;
#define BUFFER_SIZE 4096
    char buffer[BUFFER_SIZE];
    buffer[0] = '\0';
    printf("s7-playground repl\n> ");
    sc = s7_init();

    // loading a file: used for the benchmarks
    if (argc >= 2) {
        s7_load(sc, argv[1]);
        return 0;
    }

    s7_pointer out,err;
    out = err = s7_nil(sc);
    do
    {
        int len = strlen(buffer);
        fgets(buffer+len, BUFFER_SIZE-len, stdin);
        // example of a string that gets parsed and doesn't produce read-error
        // but format-error
//         strcpy(buffer,
// "(begin (define-macro (examples . args)"
// "  `(for-each (lambda (exp)"
// "	       (format #f \"~A\n\" exp))               "
// );

        s7_pointer port = s7_open_input_string(sc, buffer);

        s7_close_output_port(sc, out);
        s7_close_output_port(sc, err);

        // stdout
        out = s7_open_output_string(sc);
        s7_set_current_output_port(sc, out);

        err = s7_open_output_string(sc);
        s7_set_current_error_port(sc, err);

        s7_read(sc, port);
        // at some point I was checking against "read-error" symbol
        // but once, when reading an incomplete form that contained a format call
        // I got a "format-error" result as symbol
        // .. so.. resorting back to checking error output
        const char *errmsg = s7_get_output_string(sc, err);
        if ((errmsg) && (*errmsg)) {
            // read-error
        } else {
            s7_close_output_port(sc, out);
            s7_close_output_port(sc, err);

	    // stdout
            out = s7_open_output_string(sc);
            s7_set_current_output_port(sc, out);

	    // stderr
            err = s7_open_output_string(sc);
            s7_set_current_error_port(sc, err);

            s7_pointer result = s7_eval_c_string(sc, buffer);

            s7_pointer result_list = s7_list(sc, 3,
                                             result,
                                             s7_make_string(sc, s7_get_output_string(sc, out)),
                                             s7_make_string(sc, s7_get_output_string(sc, err))
                                            );

            char* result_list_str = s7_object_to_c_string(sc, result_list);
            printf("%s\n> ", result_list_str);

            free(result_list_str);
            // cleanup buffer
            buffer[0] = '\0';
        }


    } while(true);

    // todo s7_free
    // gotta update s7 version
}
