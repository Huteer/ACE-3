//
// Created by rositsa on 10/11/18.
//

#include <stdlib.h>
#include "instructions.h"
#include "helpfunctions.h"

void halt() {

    system(EXIT_SUCCESS);

}

void load(registers *r, char* array) {

    r->mar = binToDec12(array, r);
    r->mbr = binToDec16(array, r);
    r->ac = r->mbr;
}

void store(registers *r, char* array){

    r->mar = binToDec12(array, r);
    r->mbr = r->ac;
    *(array + r->mar*16) = decToBin(r->mbr);
}

