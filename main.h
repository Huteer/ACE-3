#pragma once

#define WORD_SIZE 16
#define MEM_SIZE 4096
#define HALT "0000"

typedef struct { char* key; int bin; int val; } int_dictionary;

static int_dictionary opcodes[] =
{
	{ "HALT", 0, 0 },
	{ "LOAD", 1, 1 },
	{ "STORE", 10, 2 },
	{ "ADD", 11, 3 },
	{ "SUB", 100, 4 },
	{ "INPUT", 101, 5 },
	{ "OUTPUT", 110, 6 },
	{ "SKIPCOND", 111, 7 },
	{ "JUMP", 1000, 8 },
	{ "LDC", 1001, 9 },
	{ "SHIFTL", 1010, 10 },
	{ "SHIFTR", 1011, 11 },
};

void read_file(char *filename);
void read_console();
void load_defaults();
char* get_opcode(char* instruction);
int validate_binary(char *bin);
void clear_memory();
void display_memory();

char memory[MEM_SIZE][WORD_SIZE + 1];
