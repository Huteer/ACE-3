//
// Created by rositsa on 10/11/18.
//

#include <stdlib.h>
#include "instructions.h"
#include "helpfunctions.h"

void halt(struct reg *cpu, char *array) {

    system(EXIT_SUCCESS);

}

void load(struct reg *cpu, char* array) {

    cpu->mar = binToDec12(array, cpu);
    cpu->mbr = binToDec16(array, cpu);
    cpu->ac = cpu->mbr;
}

void store(struct reg* cpu, char* array){

    cpu->mar = binToDec12(array, cpu);
    cpu->mbr = cpu->ac;
    *(array + cpu->mar*16) = decToBin(cpu->mbr);
}

