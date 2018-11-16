//
// Created by rositsa on 10/11/18.
//

#ifndef ACE3_INSTRUCTIONS_H
#define ACE3_INSTRUCTIONS_H

#include "structreg.h"

void halt();
void load(registers *r, char* array);
void store(registers *r, char* array);
void add(registers *r, char* array);
void subt(registers *r, char* array);
void input(registers *r);
void output(registers *r);
void skipcond(registers *r, char* array);
void jump(registers *r, char* array);
void ldc(registers *r, char* array);
void shiftr(registers *r, char* array);
void shiftl(registers *r, char* array);

#endif //ACE3_INSTRUCTIONS_H
