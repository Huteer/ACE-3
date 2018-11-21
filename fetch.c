//Code for the fetch execute cylce:
int fetchExecute();


int fetchExecute(struct ref *r)
{
	int opCode = 1;
	
	while(opCode != 0)
	{
		char temp[1][17] = {0};
		short opCode = get_opcode(memory[r->pc][WORD_SIZE + 1]);
		r->ir = memory[r->pc];
		r->mar = r->mbr << 4;
		r->mbr = getOperand(memory[r->pc][WORD_SIZE + 1]);
		
		switch(opCode)
		{
		case 1://LoadX
			temp[1][WORD_SIZE + 1] = memory[r->mbr][WORD_SIZE + 1];
			r->ac = binToDec(temp[1][WORD_SIZE +1]);
			break;
		case 2://StoreX
			memory[r->mbr][WORD_SIZE +1] = dectoBin(r->ac);
			break;
		case 3://AddX
			r->ac = r->ac + r->mbr;
			break;
		case 4://SubX
			r->ac = r->ac - r->mbr;
			break;
		case 5://Input
			read_console();
			break;
		case 6://Output
			printf("%d is the current value in the Accumulator", &r->ac);
			break;
		case 7://SkipCond
			if (r->ac == 0)
			{
				r->pc ++;				
			}
			break;
		case 8://Jump
			r->pc = r->mar;
			break;
		case 9://LDC
			r->ac = r->mar;
			break;
		case 10://ShiftR
			r->ac = r->ac/2;
			break;
		case 11://ShiftL
			r->ac = r->ac*2;
			break;
		default:
			break;
		}
		r->pc++;
	}
}
