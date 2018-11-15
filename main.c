#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include "instructions.h"
#include "structreg.h"
#include "helpfunctions.h"

#define WORD_SIZE 16
#define MEM_SIZE 4096
#define HALT "0000"

void read_file(char *filename);
void read_console();
void load_defaults();
int validate_binary(char *bin);
void clear_memory();
void display_memory();

char memory[MEM_SIZE][WORD_SIZE + 1];

int main(int argc, char *argv[])
{

    char* memoryptr = memory;

    struct reg* cpu = malloc(sizeof(struct reg));
    memset(cpu, 0, sizeof(struct reg));

    if (argc < 2)
    {
        printf("Missing argument(s)...\nTo load a program from a file use command '-f' followed by the filename.\nTo load a program from the console use command '-c'\nTo load the default program use command '-d'.\n");
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

    printf("%d\n", binToDec12(memoryptr, cpu));
    printf("%d\n", binToDec16(memoryptr, cpu));
    printf("%s\n", decToBin(binToDec12(memoryptr, cpu)));

    printf("%d\n", cpu->pc);
    printf("%d\n", cpu->ac);
    load(cpu, memoryptr);
    printf("%d", cpu->ac);
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
    char line[17], op[5];
    int isData = 0, memIndex = 0;

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
                memcpy(op, &line, 4); // Gets opcode from line
                op[4] = '\0';

                if (!strcmp(op, HALT)) // Checks for HALT opcode. When received, loads remaining lines as data
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
        fclose(fp);
        printf("File loaded successfully!\n");
    }
}

/*
	Stores binary strings entered by user into memory
*/
void read_console()
{
    char line[18], op[5];
    int memIndex = 0;

    printf("Please enter the program instructions as 16 bit binary strings:\n\n");

    while (strcmp(op, HALT)) // Stores strings as instuctions until HALT opcode is received
    {
        fgets(line, sizeof(line), stdin);

        if (line[strlen(line) - 1] == '\n') // Removes new line character
            line[strlen(line) - 1] = '\0';

        if (!validate_binary(line)) // Make sure line is a valid 16 bit binary string
        {
            printf("Line entered did not contain a 16 bit binary string.\n");
            continue;
        }

        memcpy(op, &line, 4); // Gets opcode
        op[4] = '\0';
        strcpy(memory[memIndex], line); // Stores line in memory
        memIndex++;
    }

    memIndex = 2048;
    printf("\nPlease enter the program data as 16 bit binary strings, when finished type 'run':\n\n");

    while (strcmp(line, "run")) // Stores strings as data until 'run' is entered
    {
        fgets(line, sizeof(line), stdin);

        if (line[strlen(line) - 1] == '\n') // Removes new line character
            line[strlen(line) - 1] = '\0';

        if (!validate_binary(line)) // Make sure line is a valid 16 bit binary string
        {
            printf("Line entered did not contain a 16 bit binary string.\n");
            continue;
        }

        strcpy(memory[memIndex], line); // Stores line in memory
        memIndex++;
    }
    printf("Your program is being executed...\n\n");
}

/*
	Loads default program into memory
*/
void load_defaults()
{
    strcpy(memory[0], "0001100000000000");
    strcpy(memory[1], "0011100000000001");
    strcpy(memory[2], "0010100000000010");
    strcpy(memory[3], "0000000000000000");
    strcpy(memory[2048], "0000000000000110");
    strcpy(memory[2049], "0000000000000101");
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
    for (int i = 0; i < MEM_SIZE; i++)
    {
        if (memory[i][0] != '\0')
            printf("Memory address (hex): 0x%04x\tMemory Contents (bin): %s\n", i, memory[i]);
    }
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
