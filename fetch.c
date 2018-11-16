//Code for the fetch execute cylce:

short AC = 0,IR = 0,MBR = 0,PC = 0,MAR = 0;
int fetchExecute();


int fetchExecute ()
{
	AC = 0;
	PC = 0;
	opCode = 1;
	
while(opCode != 0)
	{
		char temp[1][17] = {0};
		short opCode = getOpcode(memory[PC][WORD_SIZE + 1]);
		IR = memory[PC];
		MBR = getOperand(memory[PC][WORD_SIZE + 1];
		
		switch(opCode)
		{
		case 1://LoadX
			temp[1][WORD_SIZE + 1] = memory[MBR][WORD_SIZE + 1]
			AC = binToDec(temp[1][WORD_SIZE +1]
			break;
		case 2;//StoreX
			memory[MBR][WORD_SIZE +1] = dectoBin(AC);
			break;
		case 3://AddX
			AC = AC + MBR;
			break;
		case 4;//SubX
			AC = AC - MBR;
			break;
		case 5://Input
			read_console();
			break;
		case 6;//Output
			printf("%d is the current value in the Accumulator", &AC);
			break;
		case 7://SkipCond
			if (AC == 0)
			{
			break;
			}
		case 8;//Jump
			PC = MBR;
			break;
		case 9://LDC
			AC = MBR;
			break;
		case 10;//ShiftR
			AC = AC/2
			break;
		case 11;//ShiftL
			AC = AC*2;
			break;
		default;
			break;
		}
		PC++;
	}
}
