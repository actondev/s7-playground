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
#define BUFFER_SIZE 1024
    char buffer[BUFFER_SIZE];
    buffer[0] = '\0';
    printf("s7-playground repl\n> ");

    sc = s7_init();                 /* initialize the interpreter */
    s7_pointer out,err;
    out = err = s7_nil(sc);
    s7_pointer read_error_symbol = s7_make_symbol(sc, "read-error");
    do                       /* fire up a read-eval-print loop */
    {
        int len = strlen(buffer);
        fgets(buffer+len, BUFFER_SIZE-len, stdin);

        s7_pointer port = s7_open_input_string(sc, buffer);

        s7_close_output_port(sc, out);
        s7_close_output_port(sc, err);

        // stdout
        out = s7_open_output_string(sc);
        s7_set_current_output_port(sc, out);

        err = s7_open_output_string(sc);
        s7_set_current_error_port(sc, err);

        s7_pointer form = s7_read(sc, port);

        if (s7_is_equivalent(sc, form, read_error_symbol)) {
            // read-error

        } else {
            // eval

            // seems to be ok
            s7_close_output_port(sc, out);
            s7_close_output_port(sc, err);

            // stdout
            out = s7_open_output_string(sc);
            s7_set_current_output_port(sc, out);

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
