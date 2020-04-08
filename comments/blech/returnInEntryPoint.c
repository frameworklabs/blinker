/*
** This is generated code - do not touch!
*/

#include <stdio.h>
#include <string.h>

/*
** used C headers
*/



/*
** blech types
*/

#include "blech.h"

/*
** exports, user types and C wrappers
*/

#include "blech/returnInEntryPoint.h"

/*
** direct C constants
*/



/*
** direct C functions
*/



/*
** parameters
*/



/*
** state
*/

static blc_bool blc_main_retvar;
static blc_pc_t pc_1;

/*
** activities and functions
*/

static blc_pc_t blc_main (const blc_bool blc_a,
                          blc_bool *blc_b,
                          blc_pc_t *pc_1,
                          blc_bool *blc_retvar) {
    loopHead:
    if ( *pc_1 == 2 ) {
        *pc_1 = 5; /* proceed from surface to depth */
    }
    if ( *pc_1 == 4 ) {
        if ( 1 ) {
            (*blc_retvar) = (blc_a || (*blc_b));
            *pc_1 = 0;
        }
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(*pc_1);
    return *pc_1 ;
}

/*
** blech program
*/

void blc_blech_returnInEntryPoint_tick (const blc_bool blc_main_a,
                                        blc_bool *blc_main_b) {
    blc_main(blc_main_a, blc_main_b, &pc_1, &blc_main_retvar);
}

void blc_blech_returnInEntryPoint_init (void) {
    pc_1 = 2;
}

void blc_blech_returnInEntryPoint_printState (const blc_bool blc_main_a,
                                              blc_bool *blc_main_b) {
    printf ("\t\t\t\"pcs\": {\n\t\t\t\t\"pc_1\" : %u\n\t\t\t},\n", pc_1);
    printf("\t\t\t\"vars\": {\n");printf("\t\t\t\t\"a_line2\" : ");printf("%d", blc_main_a);
	printf(",\n");
	printf("\t\t\t\t\"b_line2\" : ");printf("%d", (*blc_main_b));printf("\n\t\t\t}\n");
}