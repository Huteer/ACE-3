# stuff to go here to show we done the work :D
1 a) + b)
Opcode	Description
Binary	Mnemonic

0000	Halt:	Terminate the program.
0001	Load X:	Load the contents of address X into AC.

0010	Store X:	Store the contents of AC to address X.

0011	Add X:	Add the contents of address X to AC and store the result in AC.

0100	Subt X: Subtract the contents of address X from AC and store the result in AC.

0101	Input:	Input a value from the keyboard into AC.

0110	Output:	Output the value in AC to the display

0111	Skipcond:	Skip the next instruction on condition.

1000	Jump X:	Load the value of X into PC.

1001	LDC X:	Load the value of X into AC.

1010	SHIFTR X:	Load the contents of address X into AC and shift right by 1.

1011	SHIFTL X:	Load the contents of address X into AC and shift left by 1.


c) skip if the AC is equal to 0

•	Binary, two’s complement representation – first bit represents a negative value
•	Stored program, fixed word length (4K words of main memory) – define two-dimensional array [4000][16] type String - 16-bit instructions, 4 for the opcode and 12 for the operand
•	AC (accumulator) – 16bits
•	IR (instruction register) – 16bits
•	MBR (memory buffer register) – 16bits
•	PC (program counter) – 12 bits
•	MAR (memory address register) – 12bits
•	InREG
•	OutREG
•	There is a status or flag register that holds information indicating conditions – ex.: overflow in the ALU

Code
1)	Define array [4000][16]
2)	Ask whether the instructions to come from a) file, b) user input, c) default content
a)	Read from a self-prepared file, consisting of instructions presented in binary -> store the info into the array
Example:
00010000001111
10010000000011
………….
Try to do a meaningful instructions file.
        
b)	Display to the user the different options for instructions and description -> Read input(option: input = “exit” which means stop reading the user input) -> transform input to binary OR give to the user meaningful instructions how to give their input as binary representation -> store into the array
c)	Directly load binary instructions into the array
3)	Display the memory contents on the screen with the respective memory locations
Example:
0    00010000001111
1    10010000000011
2    ………….
………………
4)	Convert the memory contents to assembly language and display it on the screen
Example:
Load 15
LDC 3
……………………

Main function
int main(int argc, char *argv[])
{

char array[4000][16];
//initialize registers
	If(argc < 2)
	{
		printf(“Missing argument.\n”);
		//here should be put an informative message about the expected arguments 
		printf(“Program terminated.\n”)

		return 1;
	}
	
	switch (argv[1]){
		case ‘-f’: {
				do file input
…………….
…………….




Help functions
1)	String decToBin (int x) – convert an int from decimal representation to binary and return a String
2)	Int binToDec(array) – convert a string representing binary to decimal and return an int
