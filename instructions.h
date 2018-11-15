//
// Created by rositsa on 10/11/18.
//

#ifndef ACE3_INSTRUCTIONS_H
#define ACE3_INSTRUCTIONS_H

#include "structreg.h"

void halt(struct reg* cpu, char* array);
void load(struct reg* cpu, char* array);
void store(struct reg* cpu, char* array);
void add(struct reg* cpu, char* array);
void subt(struct reg* cpu, char* array);
void input(struct reg* cpu);
void output(struct reg* cpu);
void skipcond(struct reg* cpu, char* array);
void jump(struct reg* cpu, char* array);
void ldc(struct reg* cpu, char* array);
void shiftr(struct reg* cpu, char* array);
void shiftl(struct reg* cpu, char* array);

#endif //ACE3_INSTRUCTIONS_H
