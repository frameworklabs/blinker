/*
** This is generated code - do not touch!
*/

/*
** used C headers
*/

#include <stdio.h>

/*
** blech types
*/

#include "blech.h"

/*
** the generated blech program
*/

#include "blech/returnInEntryPoint.c"

/*
** external state for the blech program
*/

static blc_bool blc_main_a;
static blc_bool blc_main_b;

/*
** the test main loop
*/

 int main(void) {
    int running = 0; /* number of iterations */
    int bound = 60;
    printf("{\n\t\"trace\":[\n");

    blc_blech_returnInEntryPoint_init();

    while( running < bound )
    {
        /* call tick function */

        blc_blech_returnInEntryPoint_tick(blc_main_a, &blc_main_b);
    
        /* display program state */
        printf ("\t\t{\n\t\t\t\"tick\": %i,\n", running);

        blc_blech_returnInEntryPoint_printState(blc_main_a, &blc_main_b);

        ++running;       
        running < bound?printf("\t\t},\n"):printf("\t\t}\n");
    }
    printf("\t]\n}");
    return 0; /* OK */
}