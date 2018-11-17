#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include "main.h"
#include "instructions.h"
#include "structreg.h"
#include "helpfunctions.h"

int main(int argc, char *argv[])
{

    char* memoryptr = *memory;
    registers cpu = {0, 0, 0, 0, 0};

    if (argc < 2)
    {
		printf("Missing argument(s)...\n");
		printf("To load a program from a file use command '-f' followed by the filename.\n");
		printf("To load a program from the console use command '-c'\n");
		printf("To load the default program use command '-d'. \n");
        return 1;
    }

    if (!strcmp(argv[1], "-f"))
    {
        if (argc < 3)
        {
            printf("No filename specified, program terminating...\n");
            return 1;
        }
        read_file(argv[2]);
    }
    else if (!strcmp(argv[1], "-c"))
    {
        read_console();
    }
    else if (!strcmp(argv[1], "-d"))
    {
        printf("Loading default program into memory...\n");
        load_defaults();
    }

    display_memory();

    printf("%d\n", binToDec12(memoryptr, &cpu));
    printf("%d\n", binToDec16(memoryptr, &cpu));
    printf("%s\n", decToBin(binToDec12(memoryptr, &cpu)));

    printf("%d\n", cpu.pc);
    printf("%d\n", cpu.ac);
    load(&cpu, memoryptr);
    printf("%d\n", cpu.ac);
    //store(cpu, memoryptr);

    display_memory();

    return 0;
}

/*
	Loads binary contents of file into memory
*/
void read_file(char *filename)
{
	FILE *fp;
	char line[17];
	char* op;
	int isData = 0, memIndex = 0, opInt = 0;

	clear_memory();
	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		printf("Failed to open file: %s\nProgram terminating...", filename);
		exit(EXIT_FAILURE);
		return;
	}
	else
	{
		printf("Opening '%s'...\n", filename);

		while (fgets(line, sizeof(line), fp)) // Reads each line in file
		{
			if (line[strlen(line) - 1] == '\n') // Removes new line character
				line[strlen(line) - 1] = '\0';

			fseek(fp, 2, SEEK_CUR); // Ignores UTF-8 hidden characters

			if (!validate_binary(line)) // Make sure line is a valid 16 bit binary string
			{
				printf("Line could not be read into 0x%04x, moving on...\n", memIndex);
				continue;
			}

			if (!isData)
			{
				op = get_opcode(line);
				opInt = atoi(op);

				if (opInt == opcodes->bin) // Checks for HALT opcode. When received, loads remaining lines as data (opcodes + 0 == HALT)
				{
					strcpy(memory[memIndex], line); // Stores HALT as instruction, required for running program
					memIndex = MEM_SIZE / 2; // Data stored halfway up memory (ie. 2048+)
					isData = 1;
					continue;
				}
			}
			strcpy(memory[memIndex], line); // Stores line in memory
			memIndex++;
		}
		printf("File loaded successfully!\n");
		fclose(fp);
	}
}

/*
	Stores binary strings entered by user into memory
*/
void read_console()
{
	char line[18];
	char* op = "\0";
	int stop = 0, memIndex = 0, opInt = 1;

	clear_memory();

	printf("Please enter the program instructions as 16 bit binary strings:\n\n");

	while (opInt != opcodes->bin) // Stores strings as instuctions until HALT opcode is received (opcodes + 0 == HALT)
	{
		fgets(line, sizeof(line), stdin);

		if (line[strlen(line) - 1] == '\n') // Removes new line character
			line[strlen(line) - 1] = '\0';

		if (!strcmp(line, "stop"))
		{
			printf("Finished taking input...\n");
			stop = 1;
			break;
		}

		if (!validate_binary(line) && strcmp(line, "stop")) // Make sure line is a valid 16 bit binary string
		{
			printf("Line entered did not contain a 16 bit binary string.\n");
			continue;
		}

		op = get_opcode(line);
		opInt = atoi(op);
		strcpy(memory[memIndex], line); // Stores line in memory
		memIndex++;
	}

	if (!stop)
	{
		memIndex = 2048;
		printf("\nPlease enter the program data as 16 bit binary strings, when finished type 'run':\n\n");

		while (strcmp(line, "run")) // Stores strings as data until 'run' is entered
		{
			fgets(line, sizeof(line), stdin);

			if (line[strlen(line) - 1] == '\n') // Removes new line character
				line[strlen(line) - 1] = '\0';

			if (!strcmp(line, "run"))
				break;

			if (!validate_binary(line) && strcmp(line, "run")) // Make sure line is a valid 16 bit binary string
			{
				printf("Line entered did not contain a 16 bit binary string.\n");
				continue;
			}

			strcpy(memory[memIndex], line); // Stores line in memory
			memIndex++;
		}
	}
	printf("Your program is being executed...\n\n");
}

/*
Loads default program into memory
*/
void load_defaults()
{
	clear_memory();
	strcpy(memory[0], "0001100000000000");
	strcpy(memory[1], "0011100000000001");
	strcpy(memory[2], "0010100000000010");
	strcpy(memory[3], "0000000000000000");
	strcpy(memory[2048], "0000000000110111");
	strcpy(memory[2049], "0000000110000101");
}

/*
Returns opcode (first 4 digits) of single binary instruction
*/
char* get_opcode(char* instruction)
{
	char* opcode = malloc(sizeof(char));
	memcpy(opcode, instruction, 4);
	opcode[4] = '\0';
	return opcode;
}

/*
	Checks input is a valid 16 bit binary string
*/
int validate_binary(char *bin)
{
    if (strlen(bin) != WORD_SIZE)
        return 0;

    for (int i = 0; i < WORD_SIZE; i++)
    {
        if (bin[i] != '0' && bin[i] != '1')
            return 0;
    }
    return 1;
}

/*
	Sets all characters in allocated memory to null
*/
void clear_memory()
{
    for (int i = 0; i < MEM_SIZE; i++)
    {
        for (int j = 0; j < WORD_SIZE; j++)
            memory[i][j] = '\0';
    }
}

/*
	Outputs memory addresses that are occupied along with their contents
*/
void display_memory()
{
	int memSize = 0;

	for (int i = 0; i < MEM_SIZE; i++)
	{
		if (memory[i][0] != '\0')
		{
			memSize++;
			printf("Memory address (hex): 0x%04x\tMemory Contents (bin): %s\n", i, memory[i]);
		}
	}

	printf("Memory Used: %d bytes\n", memSize * 2);
}

/*
int main(int argc, char *argv[]) {

    char array[4000][16];
    char *arrayptr = &array[0][0];

    struct reg* cpu = malloc(sizeof(struct reg));
    memset(cpu, 0, sizeof(struct reg));

    if(argc < 2){
        printf("Missing argument.\n");
        //here should be put an informaive message about the expected arguments
        printf("Program terminated.\n");

        return 1;
    }

    if(!strcmp(argv[1], "-f")){
        printf("%d", cpu->pc*16);
            //argv[2] is where the text file will be if you gave it as an argument when running the program

        }
        else if(!strcmp(argv[1], "-c")){

            fgets(arrayptr, 17, stdin);
        printf("%d", binToDec12(arrayptr, cpu));

        }
    else if(!strcmp(argv[1], "-d")){
            //default content
        }

    return 0;


}
 */
