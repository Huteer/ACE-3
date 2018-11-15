//
// Created by rositsa on 11/11/18.
//

#ifndef ACE3_HELPFUNCTIONS_H
#define ACE3_HELPFUNCTIONS_H

#include "structreg.h"

int binToDec12(char* array, struct reg* cpu);
int binToDec16(char* array, struct reg* cpu);
char* decToBin(int x);


#endif //ACE3_HELPFUNCTIONS_H
