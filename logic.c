
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "logic.h"

int Player;
int SixInRow;
int bluepiece;

void SetValues()
{

	for (int a = 0; a <= 3; a++)
	{
		PieceLocation[a].Red = -10;
		PieceLocation[a].Green = -10;
		PieceLocation[a].Yellow = -10;
		PieceLocation[a].Blue = -10;
		path[a].Red = -1;
		path[a].Green = -1;
		path[a].Yellow = -1;
		path[a].Blue = -1;
		BlockPath[a].Red = -1;
		BlockPath[a].Green = -1;
		BlockPath[a].Yellow = -1;
		BlockPath[a].Blue = -1;
		BasePiece.Red = 4;
		BasePiece.Green = 4;
		BasePiece.Yellow = 4;
		BasePiece.Blue = 4;
		bluepiece = 1;
		GotHome.Red = 0;
		GotHome.Green = 0;
		GotHome.Yellow = 0;
		GotHome.Blue = 0;
	}
}

void intro()
{
	printf("The red player has four (04) pieces named R1, R2, R3, and R4.\n");
	printf("The green player has four (04) pieces named G1, G2, G3, and G4.\n");
	printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
	printf("The blue player has four (04) pieces named B1, B2, B3, and B4\n");
	printf("\n");
}

void PlayerCol(int plyer)
{
	switch (plyer)
	{
	case 1:
		printf("Red");
		break;
	case 2:
		printf("Green");
		break;
	case 3:
		printf("Yellow");
		break;
	case 4:
		printf("Blue");
		break;
	}
}

int Roll()
{
	return ((rand() % 6) + 1);
}

void ChooseFirstPlayer()
{
	int maxplayer = 0, maxroll = 0;
	for (int i = 1; i <= 4; i++)
	{
		int roll = Roll();
		PlayerCol(i);
		printf(" rolls %d\n", roll);
		if (maxroll < roll)
		{
			maxplayer = i;
			maxroll = roll;
		}
	}
	Player = maxplayer;
	PlayerCol(maxplayer);
	printf(" player has the highest roll and will begin the game.\n");
	printf("The order of a single round is");
	for (int i = 1; i <= 4; i++)
	{
		printf(", ");
		if (maxplayer > 4)
		{
			maxplayer = 1;
		}
		PlayerCol(maxplayer);
		maxplayer++;
	}
	Player = maxplayer;
	printf(".\n");
}

int Move(int location, int roll)
{
	if(location > 51){
		location -= 52;
	}else if(location < 0) {
		location += 52;
	}
	int returnval = 0;
	if (block[location] > 0)
	{
		int move = 0, hadablock = 0;
		if(block[location] > 1) {					// block move if there's a block infront of it
		move = roll / block[location];
		}else {
			move = roll;
		}
		int havetojump = move;
		int otherblock;
		short thepath = piecepath(location);
		if(thepath == 0) {
			otherblock = location + 1;
		}else {
			otherblock = location - 1;
		}
		for (int run4times = 1 ; run4times <= move ; run4times++)    // chock if there are any block within the move
		{
			if(otherblock > 51) {
				otherblock -= 52;
			}else if(otherblock < 0) {
				otherblock += 52;
				}

			if (block[otherblock] > block[location])
			{
				hadablock = 1;
				if (move >= abs(otherblock - location))
				{
					move = abs(otherblock - location) - 1;
				}

				if (block[location] > 1)
				{ // block move if there's a block infront of it
					PlayerCol(Player);
					printf(" pieces ");
					for (int locpiece = 1; locpiece <= 4; locpiece++)
					{
						switch (Player)
						{
						case 1:
							if (PieceLocation[locpiece - 1].Red == location)
							{
								if (BlockPath[locpiece - 1].Red == 0)
								{
									PieceLocation[locpiece - 1].Red += move;
									if(PieceLocation[locpiece - 1].Red > 51) {
										PieceLocation[locpiece - 1].Red -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location]--;
										block[location + move]++;
									}
									printf("R%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Red == 1)
								{
									PieceLocation[locpiece - 1].Red -= move;
									if(PieceLocation[locpiece - 1].Red < 0) {
										PieceLocation[locpiece - 1].Red += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location]--;
										block[location - move]++;
									}
									printf("R%d, ", locpiece);
								}
							}
							break;
						case 2:
							if (PieceLocation[locpiece - 1].Green == location)
							{
								if (BlockPath[locpiece - 1].Green == 0)
								{
									PieceLocation[locpiece - 1].Green += move;
									if(PieceLocation[locpiece - 1].Green > 51) {
										PieceLocation[locpiece - 1].Green -= 52;
										block[location]--;
										block[(location + move) - 52]++;
									}else {
										block[location]--;
										block[location + move]++;
									}
									printf("G%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Green == 1)
								{
									PieceLocation[locpiece - 1].Green -= move;
									if(PieceLocation[locpiece - 1].Green < 0) {
										PieceLocation[locpiece - 1].Green += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location]--;
										block[location - move]++;
									}
									printf("G%d, ", locpiece);
								}
							}
							break;
						case 3:
							if (PieceLocation[locpiece - 1].Yellow == location)
							{
								if (BlockPath[locpiece - 1].Yellow == 0)
								{
									PieceLocation[locpiece - 1].Yellow += move;
									if(PieceLocation[locpiece - 1].Yellow > 51) {
										PieceLocation[locpiece - 1].Yellow -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location]--;
										block[location + move]++;
									}
									printf("Y%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Yellow == 1)
								{
									PieceLocation[locpiece - 1].Yellow -= move;
									if(PieceLocation[locpiece - 1].Yellow < 0) {
										PieceLocation[locpiece - 1].Yellow += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location]--;
										block[location - move]++;
									}
									printf("Y%d, ", locpiece);
								}
							}
							break;
						case 4:
							if (PieceLocation[locpiece - 1].Blue == location)
							{
								if (BlockPath[locpiece - 1].Blue == 0)
								{
									PieceLocation[locpiece - 1].Blue += move;
									if(PieceLocation[locpiece - 1].Blue > 51) {
										PieceLocation[locpiece - 1].Blue -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location]--;
										block[location + move]++;
									}
									printf("B%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Blue == 1)
								{
									PieceLocation[locpiece - 1].Blue -= move;
									if(PieceLocation[locpiece - 1].Blue < 0) {
										PieceLocation[locpiece - 1].Blue += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location]--;
										block[location - move]++;
									}
									printf("B%d, ", locpiece);
								}
							}
							break;
						}
					}
					printf(" is blocked from moving from L%d to L%d by ", location, havetojump);
					int blockedbyplayer = 0;
					int blockedbypiece = 0;
					for (int blockplayer = 1; blockplayer <= 4; blockplayer++)
					{
						for (int blockedpiece = 1; blockedpiece <= 4; blockedpiece++)
						{
							if (Piecelocation(blockedbyplayer, blockedbypiece) == otherblock)
							{
								blockedbyplayer = blockplayer;
								blockedbypiece = blockedpiece;
							}
						}
					}
					PlayerCol(blockedbyplayer);
					printf("%d\n", blockedbypiece);
					returnval = 10;
				}
				if (block[location] == 1)
				{
					int moved = 0;
					PlayerCol(Player);
					printf(" piece ");
					for (int movepiece = 1; movepiece <= 4; movepiece++)
					{
						switch (Player)
						{
						case 1:
							if (PieceLocation[movepiece - 1].Red == location)
							{
								moved = 1;
								if (path[movepiece - 1].Red == 0)
								{
									PieceLocation[movepiece - 1].Red += move;
									if(PieceLocation[movepiece - 1].Red > 51) {
										PieceLocation[movepiece - 1].Red -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location] --;
										block[location + move]++;
									}
									printf("R%d ", movepiece);
								}
								else if (path[movepiece - 1].Red == 1)
								{
									PieceLocation[movepiece - 1].Red -= move;
									if(PieceLocation[movepiece - 1].Red < 0) {
										PieceLocation[movepiece - 1].Red += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location] --;
										block[location - move]++;
									}
									printf("R%d ", movepiece);
								}
							}
							break;
						case 2:
							if (PieceLocation[movepiece - 1].Green == location)
							{
								moved = 1;
								if (path[movepiece - 1].Green == 0)
								{
									PieceLocation[movepiece - 1].Green += move;
									if(PieceLocation[movepiece - 1].Green > 51) {
										PieceLocation[movepiece - 1].Green -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location] --;
										block[location + move]++;
									}
									printf("G%d ", movepiece);
								}
								else if (path[movepiece - 1].Green == 1)
								{
									PieceLocation[movepiece - 1].Green -= move;
									if(PieceLocation[movepiece - 1].Green < 0) {
										PieceLocation[movepiece - 1].Green += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location] --;
										block[location - move]++;
									}
									printf("G%d ", movepiece);
								}
							}
							break;
						case 3:
							if (PieceLocation[movepiece - 1].Yellow == location)
							{
								moved = 1;
								if (path[movepiece - 1].Yellow == 0)
								{
									PieceLocation[movepiece - 1].Yellow += move;
									if(PieceLocation[movepiece - 1].Yellow > 51) {
										PieceLocation[movepiece - 1].Yellow -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location] --;
										block[location + move]++;
									}
									printf("Y%d ", movepiece);
								}
								else if (path[movepiece - 1].Yellow == 1)
								{
									PieceLocation[movepiece - 1].Yellow -= move;
									if(PieceLocation[movepiece - 1].Yellow < 0) {
										PieceLocation[movepiece - 1].Yellow += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location] --;
										block[location - move]++;
									}
									printf("Y%d ", movepiece);
								}
							}
							break;
						case 4:
							if (PieceLocation[movepiece - 1].Blue == location)
							{
								moved = 1;
								if (path[movepiece - 1].Blue == 0)
								{
									PieceLocation[movepiece - 1].Blue += move;
									if(PieceLocation[movepiece - 1].Blue > 51) {
										PieceLocation[movepiece - 1].Blue -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location] --;
										block[location + move]++;
									}
									printf("B%d ", movepiece);
								}
								else if (path[movepiece - 1].Blue == 1)
								{
									PieceLocation[movepiece - 1].Blue -= move;
									if(PieceLocation[movepiece - 1].Blue < 0) {
										PieceLocation[movepiece - 1].Blue += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location] --;
										block[location - move]++;
									}
									printf("B%d ", movepiece);
								}
							}
							break;
						}
					}
					printf("is blocked from moving from L%d to L%d by ", location, havetojump);
					int blockedbyplayer = 0;
					int blockedbypiece = 0;
					for (int blockplayer = 1; blockplayer <= 4; blockplayer++)
					{
						for (int blockedpiece = 1; blockedpiece <= 4; blockedpiece++)
						{
							if (Piecelocation(blockedbyplayer, blockedbypiece) == otherblock)
							{
								blockedbyplayer = blockplayer;
								blockedbypiece = blockedpiece;
							}
						}
					}
					PlayerCol(blockedbyplayer);
					printf("%d piece.\n", blockedbypiece);
					return 0;
				}

				if (abs(otherblock - location) == 0)
				{
					PlayerCol(Player);
					printf(" does not have other pieces in the board to move instead of the blocked piece.Ignoring the throw and moving on to the next player.\n");
					return 0;
				}
				if (otherblock > location)
				{
					printf("does not have other pieces in the board to move instead of the blocked piece.Moved the piece to square L%d which is the cell before the block.\n", (otherblock - 1));
				}
				else if (otherblock < location)
				{
					printf("does not have other pieces in the board to move instead of the blocked piece.Moved the piece to square L%d which is the cell before the block.\n", (otherblock + 1));
					return 0;
				}
			}
			if(thepath == 0) {
				otherblock++;
			}else {
				otherblock--;
			}

		}
		if (hadablock == 0)
			{
				int newpiecelocation = 0;
				PlayerCol(Player);
				printf(" moves piece ");

				if (block[location] > 1)
				{
					for (int locpiece = 1; locpiece <= 4; locpiece++)
					{
						switch (Player)
						{
						case 1:
							if (PieceLocation[locpiece - 1].Red == location)
							{
								if (BlockPath[locpiece - 1].Red == 0)
								{
									PieceLocation[locpiece - 1].Red += move;
									if(PieceLocation[locpiece - 1].Red > 51) {
										PieceLocation[locpiece - 1].Red -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location]--;
										block[location + move]++;
									}
									newpiecelocation = location + move;
									printf("R%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Red == 1)
								{
									PieceLocation[locpiece - 1].Red -= move;
									if(PieceLocation[locpiece - 1].Blue < 0) {
										PieceLocation[locpiece - 1].Blue += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location]--;
										block[location - move]++;
									}
									newpiecelocation = location - move;
									printf("R%d, ", locpiece);
								}
							}
							break;
						case 2:
							if (PieceLocation[locpiece - 1].Green == location)
							{
								if (BlockPath[locpiece - 1].Green == 0)
								{
									PieceLocation[locpiece - 1].Green += move;
									if(PieceLocation[locpiece - 1].Green > 51) {
										PieceLocation[locpiece - 1].Green -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location]--;
										block[location + move]++;
									}
									newpiecelocation = location + move;
									printf("G%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Green == 1)
								{
									PieceLocation[locpiece - 1].Green -= move;
									if(PieceLocation[locpiece - 1].Blue < 0) {
										PieceLocation[locpiece - 1].Blue += 52;
										block[location] --;
										block[(location + move) + 52]++;
									}else {
										block[location]--;
										block[location - move]++;
									}
									newpiecelocation = location - move;
									printf("G%d, ", locpiece);
								}
							}
							break;
						case 3:
							if (PieceLocation[locpiece - 1].Yellow == location)
							{
								if (BlockPath[locpiece - 1].Yellow == 0)
								{
									PieceLocation[locpiece - 1].Yellow += move;
									if(PieceLocation[locpiece - 1].Yellow > 51) {
										PieceLocation[locpiece - 1].Yellow -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location]--;
										block[location + move]++;
									}
									newpiecelocation = location + move;
									printf("Y%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Yellow == 1)
								{
									PieceLocation[locpiece - 1].Yellow -= move;
									if(PieceLocation[locpiece - 1].Blue < 0) {
										PieceLocation[locpiece - 1].Blue += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location]--;
										block[location - move]++;
									}
									newpiecelocation = location - move;
									printf("Y%d, ", locpiece);
								}
							}
							break;
						case 4:
							if (PieceLocation[locpiece - 1].Blue == location)
							{
								if (BlockPath[locpiece - 1].Blue == 0)
								{
									PieceLocation[locpiece - 1].Blue += move;
									if(PieceLocation[locpiece - 1].Blue > 51) {
										PieceLocation[locpiece - 1].Blue -= 52;
										block[location] --;
										block[(location + move) - 52]++;
									}else {
										block[location]--;
										block[location + move]++;
									}
									newpiecelocation = location + move;
									printf("B%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Blue == 1)
								{
									PieceLocation[locpiece - 1].Blue -= move;
									if(PieceLocation[locpiece - 1].Blue < 0) {
										PieceLocation[locpiece - 1].Blue += 52;
										block[location] --;
										block[(location - move) + 52]++;
									}else {
										block[location]--;
										block[location - move]++;
									}
									newpiecelocation = location - move;
									printf("B%d, ", locpiece);
								}
							}
							break;
						}
					}if (newpiecelocation == location)
					{
						printf(" from location L%d to L%d by %d units.\n", location, newpiecelocation, move);
					}else {
						printf(" from location L%d to L%d by %d units in ", location, newpiecelocation, move);
						if (newpiecelocation > location)
						{
							printf("clockwise direction\n");
						}
						else if (newpiecelocation < location)
						{
							printf("counter-clockwise direction\n");
						}
					}
				}
			else if (block[location] == 1)
				{
				int moved = 0;
					for (int movepiece = 1; movepiece <= 4; movepiece++)
					{
						switch (Player)
						{
						case 1:
							if (PieceLocation[movepiece - 1].Red == location)
							{
								moved = 1;
								if (path[movepiece - 1].Red == 0)
								{
									PieceLocation[movepiece - 1].Red += move;
									if(PieceLocation[movepiece - 1].Red > 51) {
										PieceLocation[movepiece - 1].Red -= 52;
										block[location] = 0;
										block[(location + move) - 52] = 1;
									}else {
										block[location] = 0;
										block[location + move] = 1;
									}
									newpiecelocation = location + move;
									printf("R%d ", movepiece);
								}
								else if (path[movepiece - 1].Red == 1)
								{
									PieceLocation[movepiece - 1].Red -= move;
									if(PieceLocation[movepiece - 1].Red < 0) {
										PieceLocation[movepiece - 1].Red += 52;
										block[location] = 0;
										block[(location - move) + 52] = 1;
									}else {
										block[location] = 0;
										block[location - move] = 1;
									}
									newpiecelocation = location - move;
									printf("R%d ", movepiece);
								}
							}
							break;
						case 2:
							if (PieceLocation[movepiece - 1].Green == location)
							{
								moved = 1;
								if (path[movepiece - 1].Green == 0)
								{
									PieceLocation[movepiece - 1].Green += move;
									if(PieceLocation[movepiece - 1].Green > 51) {
										PieceLocation[movepiece - 1].Green -= 52;
										block[location] == 0;
										block[(location + move) - 52] = 1;
									}else {
										block[location] = 0;
										block[location + move] = 1;
									}
									newpiecelocation = location + move;
									printf("G%d ", movepiece);
								}
								else if (path[movepiece - 1].Green == 1)
								{
									PieceLocation[movepiece - 1].Green -= move;
									if(PieceLocation[movepiece - 1].Green < 0) {
										PieceLocation[movepiece - 1].Green += 52;
										block[location] = 0;
										block[(location - move) + 52] = 1;
									}else {
										block[location] = 0;
										block[location - move] = 1;
									}
									newpiecelocation = location - move;
									printf("G%d ", movepiece);
								}
							}
							break;
						case 3:
							if (PieceLocation[movepiece - 1].Yellow == location)
							{
								moved = 1;
								if (path[movepiece - 1].Yellow == 0)
								{
									PieceLocation[movepiece - 1].Yellow += move;
									if(PieceLocation[movepiece - 1].Yellow > 51) {
										PieceLocation[movepiece - 1].Yellow -= 52;
										block[location] = 0;
										block[(location + move) - 52] = 1;
									}else {
										block[location] = 0;
										block[location + move] = 1;
									}
									newpiecelocation = location + move;
									printf("Y%d ", movepiece);
								}
								else if (path[movepiece - 1].Yellow == 1)
								{
									PieceLocation[movepiece - 1].Yellow -= move;
									if(PieceLocation[movepiece - 1].Yellow < 0) {
										PieceLocation[movepiece - 1].Yellow += 52;
										block[location] = 0;
										block[(location - move) + 52] = 1;
									}else {
										block[location] = 0;
										block[location - move] = 1;
									}
									newpiecelocation = location - move;
									printf("Y%d ", movepiece);
								}
							}
							break;
						case 4:
							if (PieceLocation[movepiece - 1].Blue == location)
							{
								moved = 1;
								if (path[movepiece - 1].Blue == 0)
								{
									PieceLocation[movepiece - 1].Blue += move;
									if(PieceLocation[movepiece - 1].Blue > 51) {
										PieceLocation[movepiece - 1].Blue -= 52;
										block[location] = 0;
										block[(location + move) - 52] = 1;
									}else {
										block[location] = 0;
										block[location + move] = 1;
									}
									newpiecelocation = location + move;
									printf("B%d ", movepiece);
								}
								else if (path[movepiece - 1].Blue == 1)
								{
									PieceLocation[movepiece - 1].Blue -= move;
									if(PieceLocation[movepiece - 1].Blue < 0) {
										PieceLocation[movepiece - 1].Blue += 52;
										block[location] = 0;
										block[(location - move) + 52] = 1;
									}else {
										block[location] = 0;
										block[location - move] = 1;
									}
									newpiecelocation = location - move;
									printf("B%d ", movepiece);
								}
							}
							break;
						}
						if(moved == 1) {
							break;
						}
					}
					printf(" from location L%d to L%d by %d units in ", location, newpiecelocation, move);
					if (newpiecelocation > location)
					{
						printf("clockwise direction\n");
					}
					else if (newpiecelocation < location)
					{
						printf("counter-clockwise direction\n");
					}
				}
			}
	}
	if(block[location] > 0) {
		for(int piebl = 1; piebl <= 4; piebl++ ) {
			// breaked block first move
			switch (Player) {
				case 1:
					if(path[piebl - 1].Red == location && BlockPath[piebl - 1].Red == -1) {
						block[location] = 1;
						Move(location, roll);
					}
				break;
				case 2:
					if(path[piebl - 1].Green == location && BlockPath[piebl - 1].Green == -1) {
						block[location] = 1;
						Move(location, roll);
					}
				break;
				case 3:
					if(path[piebl - 1].Yellow == location && BlockPath[piebl - 1].Yellow == -1) {
						block[location] = 1;
						Move(location, roll);
					}
				break;
				case 4:
					if(path[piebl - 1].Blue == location && BlockPath[piebl - 1].Blue == -1) {
						block[location] = 1;
						Move(location, roll);
					}
				break;

			}
		}
	}

	if(location > 51) {
		location -= 52;
	}else if( location < 0) {
		location += 52;
	}
	return returnval;
}

void BaseToBoard()
{
	switch (Player)
	{
	case 1:
		for (int i = 1; i <= 4; i++) {
			if (Piecelocation(1, i) == -10)
			{
				int havetomakeablock = 0;
				BasePiece.Red--;
				printf("Red player moves piece R%d to the starting point.\n", i);
				printf("Red player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Red), BasePiece.Red);
				if(block[26] > 0) {
					for(int pie = 1; pie <= 4; pie++) {
						if(PieceLocation[pie - 1].Blue == 26 || PieceLocation[pie - 1].Green == 26 || PieceLocation[pie - 1].Yellow == 26 ) {
							printf("Red player R%d captures, ", i);
							Reset(26);
							block[26] = 1;
						}
						if(PieceLocation[pie - 1].Red == 26) {
							havetomakeablock = 1;
						}
					}
				}else if(block[26] == 0) {
					block[26] = 1;
				}
				PieceLocation[i - 1].Red = 26;
				HeadTail(i);
				if(havetomakeablock == 1) {
					makeBlockX();
				}
				break;
			}
		}
		break;
	case 2:
		for (int i = 1; i <= 4; i++)
		{
			int havetomakeablock = 0;
			if (Piecelocation(2, i) == -10) {
				BasePiece.Green--;
				printf("Green player moves piece G%d to the starting point.\n", i);
				printf("Green player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Green), BasePiece.Green);
				if(block[39] > 0) {
					for(int pie = 1; pie <= 4; pie++) {
						if(PieceLocation[pie - 1].Red == 39 || PieceLocation[pie - 1].Yellow == 39 || PieceLocation[pie - 1].Blue == 39) {
							printf("Green player G%d captures, ", i);
							Reset(39);
							block[39] = 1;
						}
						if(PieceLocation[pie - 1].Green == 39) {
							havetomakeablock = 1;
						}
					}
				}else if(block[39] == 0) {
					block[39] = 1;
				}
				PieceLocation[i - 1].Green = 39;
				HeadTail(i);
				if(havetomakeablock == 1) {
					makeBlockX();
				}
				break;
			}
		}
		break;
	case 3:
		for (int i = 1; i <= 4; i++)
		{
			if (Piecelocation(3, i) == -10)
			{
				int havetomakeablock = 0;
				BasePiece.Yellow--;
				printf("Yellow player moves piece Y%d to the starting point.\n", i);
				printf("Yellow player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Yellow), BasePiece.Yellow);
				if(block[0] > 0) {
					for(int pie = 1; pie <= 4; pie++) {
						if(PieceLocation[pie - 1].Blue == 0 || PieceLocation[pie - 1].Red == 0 || PieceLocation[pie - 1].Green == 0) {
							printf("Yellow player Y%d captures, ", i);
							Reset(0);
							block[0] = 1;
						}
						if(PieceLocation[pie - 1].Yellow == 0) {
							havetomakeablock = 1;
						}
					}
				}else if(block[0] == 0) {
					block[0] = 1;
				}
				PieceLocation[i - 1].Yellow = 0;
				HeadTail(i);
				if(havetomakeablock == 1) {
					makeBlockX();
				}
				break;
			}
		}
		break;
	case 4:
		for (int i = 1; i <= 4; i++)
		{
			if (Piecelocation(4, i) == -10)
			{
				int havetomakeablock = 0;
				BasePiece.Blue--;
				printf("Blue player moves piece B%d to the starting point.\n", i);
				printf("Blue player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Blue), BasePiece.Blue);
				if(block[13] > 0) {
					for(int pie = 1; pie <= 4; pie++) {
						if(PieceLocation[pie - 1].Yellow == 13 || PieceLocation[pie - 1].Red == 13 || PieceLocation[pie - 1].Green == 13) {
							printf("Blue player B%d captures, ", i);
							Reset(13);
							block[13] = 1;
						}
						if(PieceLocation[pie - 1].Blue == 13) {
							havetomakeablock = 1;
						}
					}
				}else if(block[13] == 0) {
					block[13] = 1;
				}
				PieceLocation[i - 1].Blue = 13;
				HeadTail(i);
				if(havetomakeablock == 1) {
					makeBlockX();
				}
				break;
			}
		}
		break;
	}
}

int Piecelocation(int randplayer, int piece)
{
	int location = -10;
	switch (randplayer)
	{
	case 1:
		location = PieceLocation[piece - 1].Red;
		break;
	case 2:
		location = PieceLocation[piece - 1].Green;
		break;
	case 3:
		location = PieceLocation[piece - 1].Yellow;
		break;
	case 4:
		location = PieceLocation[piece - 1].Blue;
		break;
	}
	return location;
}

void Capture(int piece, int roll) {

	int location = Piecelocation(Player, piece);
	int move = roll / block[location];
	int newlocation = 0;
	int newlocationplus = location + move;
	int newlocationmin = location - move;
	if(newlocationplus > 52) {
		newlocationplus -= 52;
	}else if(newlocationmin < 0) {
		newlocationmin += 52;
	}
	int wheretorest = -1;
	switch (Player) {
		case 1:
			printf("Red piece ");
		for (int p = 1; p <= 4; p++)
		{
			if(block[location] > 1 && BlockPath[p - 1].Red == 0) {
				if (PieceLocation[p - 1].Red == newlocationplus)
				{
					printf("R%d, ", p);
					captured[p - 1].Red++;
					wheretorest = 0;
					newlocation = newlocationplus;
				}
			}else if(block[location] > 1 && BlockPath[p - 1].Red == 1 && PieceLocation[p - 1].Red == newlocationmin) {
				if (PieceLocation[p - 1].Red == newlocationmin)
				{
					printf("R%d, ", p);
					captured[p - 1].Red++;
					wheretorest = 1;
					newlocation = newlocationmin;
				}
			}else if(block[location] == 1 && path[p - 1].Red == 0) {
				if (PieceLocation[p - 1].Red == newlocationplus)
				{
					printf("R%d, ", p);
					captured[p - 1].Red++;
					wheretorest = 0;
					newlocation = newlocationplus;
				}
			}else if(block[location] == 1 && path[p - 1].Red == 1) {
				if (PieceLocation[p - 1].Red == newlocationmin)
				{
					printf("R%d, ", p);
					captured[p - 1].Red++;
					wheretorest = 1;
					newlocation = newlocationmin;
				}
			}
		}
		printf("lands on square L%d, captures ", newlocation);
		break;
		case 2:
			printf("Green piece ");
		for (int p = 1; p <= 4; p++)
		{
			if(block[location] > 1 && BlockPath[p - 1].Green == 0) {
				if (PieceLocation[p - 1].Green == newlocationplus)
				{
					printf("G%d, ", p);
					captured[p - 1].Green++;
					wheretorest = 0;
					newlocation = newlocationplus;
				}
			}else if(block[location] > 1 && BlockPath[p - 1].Green == 1) {
				if (PieceLocation[p - 1].Green == newlocationmin)
				{
					printf("G%d, ", p);
					captured[p - 1].Green++;
					wheretorest = 1;
					newlocation = newlocationmin;
				}
			}else if(block[location] == 1 && path[p - 1].Green == 0) {
				if (PieceLocation[p - 1].Green == newlocationplus)
				{
					printf("G%d, ", p);
					captured[p - 1].Green++;
					wheretorest = 0;
					newlocation = newlocationplus;
				}
			}else if(block[location] == 1 && path[p - 1].Green == 1) {
				if (PieceLocation[p - 1].Green == newlocationmin)
				{
					printf("G%d, ", p);
					captured[p - 1].Green++;
					wheretorest = 1;
					newlocation = newlocationmin;
				}
			}
		}
		printf("lands on square L%d, captures ", newlocation);
		break;
		case 3:
			printf("Yellow piece ");
			for (int p = 1; p <= 4; p++)
			{
			if(block[location] > 1 && BlockPath[p - 1].Yellow == 0) {
				if (PieceLocation[p - 1].Yellow == newlocationplus)
				{
					printf("Y%d, ", p);
					captured[p - 1].Yellow++;
					wheretorest = 0;
					newlocation = newlocationplus;
				}
			}else if(block[location] > 1 && BlockPath[p - 1].Yellow == 1) {
				if (PieceLocation[p - 1].Yellow == newlocationmin)
				{
					printf("R%d, ", p);
					captured[p - 1].Yellow++;
					wheretorest = 1;
					newlocation = newlocationmin;
				}
			}else if(block[location] == 1 && path[p - 1].Yellow == 0) {
				if (PieceLocation[p - 1].Yellow == newlocationplus)
				{
					printf("R%d, ", p);
					captured[p - 1].Yellow++;
					wheretorest = 0;
					newlocation = newlocationplus;
				}
			}else if(block[location] == 1 && path[p - 1].Yellow == 1) {
				if (PieceLocation[p - 1].Yellow == newlocationmin)
				{
					printf("R%d, ", p);
					captured[p - 1].Yellow++;
					wheretorest = 1;
					newlocation = newlocationmin;
				}
			}
		}
		printf("lands on square L%d, captures ", newlocation);
		break;
		case 4:
			printf("Blue piece ");
		for (int p = 1; p <= 4; p++)
		{
			if(block[location] > 1 && BlockPath[p - 1].Blue == 0) {
				if (PieceLocation[p - 1].Blue == newlocationplus)
				{
					printf("R%d, ", p);
					captured[p - 1].Blue++;
					wheretorest = 0;
					newlocation = newlocationplus;
				}
			}else if(block[location] > 1 && BlockPath[p - 1].Blue == 1) {
				if (PieceLocation[p - 1].Blue == newlocationmin)
				{
					printf("R%d, ", p);
					captured[p - 1].Blue++;
					wheretorest = 1;
					newlocation = newlocationmin;
				}
			}else if(block[location] == 1 && path[p - 1].Blue == 0) {
				if (PieceLocation[p - 1].Blue == newlocationplus)
				{
					printf("R%d, ", p);
					captured[p - 1].Blue++;
					wheretorest = 0;
					newlocation = newlocationplus;
				}
			}else if(block[location] == 1 && path[p - 1].Blue == 1) {
				if (PieceLocation[p - 1].Blue == newlocationmin)
				{
					printf("R%d, ", p);
					captured[p - 1].Blue++;
					wheretorest = 1;
					newlocation = newlocationmin;
				}
			}
		}
		printf("lands on square L%d, captures ", newlocation);
		break;
	}
		if(wheretorest == 0) {
			Reset(newlocationplus);
		}else if(wheretorest == 1) {
			Reset(newlocationmin);
		}
		Move(location, roll);
}
void Reset(int location)
{
	int Basepiece = 0;
	int capturedplayer = 0;
    for (int r = 1; r <= 4; r++)
    {
    	for (int s = 1; s <= 4; s++)
    		{
    		switch (r)
    		{
    			case 1:
    				if (PieceLocation[s - 1].Red == location)
    				{
    					PieceLocation[s - 1].Red = -10;
    					captured[s - 1].Red = 0;
    					++BasePiece.Red;
    					path[s - 1].Red = -1;
    					printf("R%d, ", s);
    					Basepiece = BasePiece.Red;
    					capturedplayer = 1;
    				}
    			break;
    			case 2:
    				if (PieceLocation[s - 1].Green == location)
    				{
    					PieceLocation[s - 1].Green = -10;
    					captured[s - 1].Green = 0;
    					++BasePiece.Green;
    					path[s - 1].Green = -1;
    					printf("G%d, ", s);
    					Basepiece = BasePiece.Green;
    					capturedplayer = 2;
    				}
    			break;
    			case 3:
    				if (PieceLocation[s - 1].Yellow == location)
    				{
    					PieceLocation[s - 1].Yellow = -10;
    					captured[s - 1].Yellow = 0;
    					++BasePiece.Yellow;
    					path[s - 1].Yellow = -1;
						printf("Y%d, ", s);
    					Basepiece = BasePiece.Yellow;
    					capturedplayer = 3;
    				}
    			break;
    			case 4:
    				if (PieceLocation[s - 1].Blue == location)
    				{
    					PieceLocation[s - 1].Blue = -10;
    					captured[s - 1].Blue = 0;
    					++BasePiece.Blue;
    					path[s - 1].Blue = -1;
						printf("B%d, ", s);
    					Basepiece = BasePiece.Blue;
    					capturedplayer = 4;
    				}
    			break;
    		}
    	}
    }
	PlayerCol(capturedplayer);
	printf(" player and return to the base.\n");
	PlayerCol(capturedplayer);
	printf(" player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - Basepiece), Basepiece);
}

void AI(int roll)
{
	if (roll == 6)
	{
		SixInRow++;
	}
	if (SixInRow >= 3)
	{
		PlayerCol(Player);
		printf(" six rolled for the third consecutive time, the roll is ignored.\n");
		BreakBlock();
		return;
	}

	switch (Player){
	case 1: {
		if(BasePiece.Red < 4) {
			int cancapture[4] = {55, 55, 55, 55};
			int minval = 55;
			int choosepiece = 0;
			for (int c = 1; c <= 4; c++)
			{
				int newlocation = -20;
				if (PieceLocation[c - 1].Red >= 0 && path[c - 1].Red == 0) {
					newlocation = (PieceLocation[c - 1].Red + roll);
					if(newlocation > 51) {
						newlocation -= 52;
					}
				}
				if (PieceLocation[c - 1].Red >= 0 && path[c - 1].Red == 1) {
					newlocation = (PieceLocation[c - 1].Red - roll);
					if(newlocation < 51) {
						newlocation += 52;
					}
				}
				for (int d = 1; d <= 4; d++)
				{
					if ((newlocation == PieceLocation[d - 1].Green || newlocation == PieceLocation[d - 1].Yellow || newlocation == PieceLocation[d - 1].Blue) && (block[newlocation - roll] >= block[newlocation]))
					{
						if (path[c - 1].Red == 0)
						{
							cancapture[c - 1] = (50 - newlocation);
							break;
						}
						if (path[c - 1].Red == 1)
						{
							cancapture[c - 1] = newlocation + 2;
							break;
						}
					}
				}
			}

			for (int x = 0; x <= 3; x++)
			{
				if (cancapture[x] < minval)
				{
					minval = cancapture[x];
					choosepiece = (x + 1);
				}
			}
			if (minval != 55 && SixInRow <= 2)
			{ // Red capture if can
				Capture(choosepiece, roll);
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
			}
			int thecap = CanCapture(roll);
			if(thecap > 0) {
				Capture(thecap, roll);
			}
		}
		if (roll == 6 && BasePiece.Red > 0 ) {// Red move a piece base to board
			BaseToBoard();
			printf("%d", PieceLocation[0].Red);
			printf("%d", block[PieceLocation[0].Red]);
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}
		else if (BasePiece.Red < 4) {
			int PossibleMove = 0;
			for (int y = 1; y <= 4; y++)
			{
				for (int Piecerd = 1; Piecerd <= 4; Piecerd++)
				{
					if ((PieceLocation[Piecerd - 1].Red != (PieceLocation[y - 1].Red + roll)) && (y != Piecerd) && PieceLocation[y - 1].Red >= 0)
					{ // Move Red piece but avoid making block
						Move(PieceLocation[y - 1].Red, roll);
						PossibleMove++;
						if (roll == 6)
						{
							roll = Roll();
							PlayerCol(Player);
							printf(" player rolled %d.\n", roll);
							AI(roll);
						}
						break;
					}
				}
				if(PossibleMove == 1) {
					break;
				}
			}
			if (PossibleMove == 0)
			{
				int theblockpice = CanMakeBlock(roll);
				if( theblockpice > 0) {
					MakeABlock(PieceLocation[theblockpice - 1].Red, roll);
					Move(PieceLocation[theblockpice - 1].Red, roll);
					if (roll == 6)
					{
						roll = Roll();
						PlayerCol(Player);
						printf(" player rolled %d.\n", roll);
						AI(roll);
					}
				}else {
					SixInRow = 0;
					return;
				}
			}
		}
		SixInRow = 0;
	}
		break;
	case 2:
	{
		int block_piece = CanMakeBlock(roll);
		if (roll == 6 && block_piece > 0 && BasePiece.Green < 4)
			{
				MakeABlock(block_piece, roll);
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
			}else if (roll == 6 && BasePiece.Green > 0)
			{
				BaseToBoard();
				printf("%d", PieceLocation[0].Green);
				printf("%d", block[PieceLocation[0].Green]);
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}
		else if (BasePiece.Green < 4)
		{
			int piecehavetomove = 0, isitblocked = 0, blockhavetomove = 0;
			int thepiececancap = CanCapture(roll);
			if(thepiececancap > 0) {
				Capture(thepiececancap, roll);
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
			}
			for (int loop = 1; loop <= 4; loop++) {
				int randompiecelocation = PieceLocation[loop - 1].Green;
				if(randompiecelocation >= 0) {
					if (block[randompiecelocation] == 1)
					{
						piecehavetomove = loop;
					}else if (block[randompiecelocation] > 1) {
						blockhavetomove = loop;
					}
			}
			}
			if (piecehavetomove == 0 && blockhavetomove > 0) {
				piecehavetomove = blockhavetomove;
			}
			if(piecehavetomove > 0) {
				isitblocked = Move(PieceLocation[piecehavetomove - 1].Green, roll);
				if (isitblocked == 10)
				{
					BreakBlock();
				}
				if (roll == 6)
				{
					roll = Roll();
					PlayerCol(Player);
					printf(" player rolled %d.\n", roll);
					AI(roll);
				}
			}
		}
		SixInRow = 0;
		break;
	}
	case 3:
		if (roll == 6 && BasePiece.Yellow > 0)
		{
			BaseToBoard();
			printf("%d", PieceLocation[0].Yellow);
			printf("%d", block[PieceLocation[0].Yellow]);
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}
		else if( BasePiece.Yellow < 4 )
		{
			int theblockpiece = CanMakeBlock(roll);
			int cancaptureY = CanCapture(roll);
			if (cancaptureY > 0)
			{
				Capture(cancaptureY, roll);
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
			}else if(theblockpiece > 0) {
				MakeABlock(theblockpiece, roll);
				break;
			}else{
				int thepiece = 0;

				for (int closetohome = 1; closetohome <= 4; closetohome++)
				{
					int hometolocation = 55;
					if (path[closetohome - 1].Yellow == 0)
					{
						if (hometolocation > (52 - PieceLocation[closetohome - 1].Yellow) && PieceLocation[closetohome - 1].Yellow >= 0 )
						{
							thepiece = closetohome;
							hometolocation = 52 - PieceLocation[closetohome - 1].Yellow;
						}
					}
					else if (path[closetohome - 1].Yellow == 1)
					{
						if (hometolocation > (2 + PieceLocation[closetohome - 1].Yellow) && PieceLocation[closetohome - 1].Yellow >= 0)
						{
							thepiece = closetohome;
							hometolocation = 2 + PieceLocation[closetohome - 1].Yellow;
						}
					}
				}
				if (thepiece > 0)
				{
					Move(PieceLocation[thepiece - 1].Yellow, roll);
					if (roll == 6)
					{
						roll = Roll();
						PlayerCol(Player);
						printf(" player rolled %d.\n", roll);
						AI(roll);
					}
				}
			}
		}
		SixInRow = 0;
		break;

	case 4:
		if (roll == 6 && BasePiece.Blue > 0)
		{
			BaseToBoard();
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}else if( BasePiece.Blue < 4 ) {
			for(int theloop = 1; theloop <= 4; theloop++) {
				if(PieceLocation[bluepiece - 1].Blue >= 0) {

					//mystery cell scene ek

					int theblockpiece = CanMakeBlock(roll);
					int cancapture = CanCapture(roll);
					if (cancapture > 0){
						Capture(cancapture, roll);
						roll = Roll();
						PlayerCol(Player);
						printf(" player rolled %d.\n", roll);
						AI(roll);
						break;
					}if(theblockpiece > 0) {
						MakeABlock(theblockpiece, roll);
						break;
					}
					Move(PieceLocation[bluepiece - 1].Blue, roll);
						if (roll == 6) {
							roll = Roll();
							PlayerCol(Player);
							printf(" player rolled %d.\n", roll);
							AI(roll);
						}
					break;
				}
				++bluepiece;
				if(bluepiece > 4) {
					bluepiece = 1;
				}
			}
		}
		break;
	}
}

void MakeABlock(int piece, int roll)
{

	int currentlocation = Piecelocation(Player, piece);
	int oldblock = block[currentlocation];
	int newpiecepath = 0;
	int oldpiecepath = 0;
	int blockpath = 0;
	int newlocation = currentlocation + roll;

	block[currentlocation] = 0;
	if(newlocation > 51) {
		newlocation -= 52;
	}else if(newlocation < 51) {
		newlocation += 51;
	}
	block[newlocation] += oldblock;
	for (int newpiece = 1; newpiece <= 4; newpiece++)
	{
		switch (Player)
		{
		case 1:
			if (PieceLocation[newpiece - 1].Red == newlocation)
			{
				newpiecepath = path[newpiece - 1].Red;
			}
			oldpiecepath = path[piece-1].Red;
			break;
		case 2:
			if (PieceLocation[newpiece - 1].Green == newlocation)
			{
				newpiecepath = path[newpiece - 1].Green;
			} //  to get new location piece path
			oldpiecepath = path[piece - 1].Green;
			break;
		case 3:
			if (PieceLocation[newpiece - 1].Yellow == newlocation)
			{
				newpiecepath = path[newpiece- 1 ].Yellow;
			}
			oldpiecepath = path[piece - 1].Yellow;
			break;
		case 4:
			if (PieceLocation[newpiece - 1].Blue == newlocation)
			{
				newpiecepath = path[newpiece - 1].Blue;
			}
			oldpiecepath = path[piece - 1].Blue;
			break;
		}
	}

	if (newpiecepath != oldpiecepath)
	{
		if (oldpiecepath == 0)
		{
			int hometooldpiece = 0, hometonewpiece = 0;
			hometooldpiece = 52 - currentlocation + roll; // to get path of the block
			hometonewpiece = currentlocation + roll + 2;
			if (hometooldpiece > hometonewpiece)
			{
				blockpath = oldpiecepath;
			}
			else
			{
				blockpath = newpiecepath;
			}
		}
	}
	else
	{
		switch (Player)
		{
		case 1:
			blockpath = path[piece - 1].Red;
			break;
		case 2:
			blockpath = path[piece - 1].Green;
			break;
		case 3:
			blockpath = path[piece - 1].Yellow;
			break;
		case 4:
			blockpath = path[piece - 1].Blue;
			break;
		}
	}

	switch (Player)
	{
	case 1:
		BlockPath[piece - 1].Red = blockpath;
		break;
	case 2:
		BlockPath[piece - 1].Green = blockpath;
		break;
	case 3: // store the data of block path
		BlockPath[piece - 1].Yellow = blockpath;
		break;
	case 4:
		BlockPath[piece - 1].Blue = blockpath;
		break;
	}

	block[newlocation] += oldblock;
	Move(currentlocation, roll);
}

void HeadTail(int piece)
{

	int headtail = rand() % 2;   //  0 = clockwise  1 = counterwise.
	switch (Player)
	{
	case 1:
		path[piece - 1].Red = headtail;
		break;
	case 2:
		path[piece - 1].Green = headtail;
		break;
	case 3:
		path[piece - 1].Yellow = headtail;
		break;
	case 4:
		path[piece - 1].Blue = headtail;
		break;
	}
}

int randpiece()
{
	return (rand() % 4) + 1;
}

void BreakBlock()
{

	for (int blockpiece1 = 1; blockpiece1 <= 4; blockpiece1++)
	{
		for (int blockpiece2 = blockpiece1; blockpiece2 <= 4; blockpiece2++)
		{
			switch (Player)
			{
			case 1:
				if (PieceLocation[blockpiece1 - 1].Red == PieceLocation[blockpiece2 - 1].Red && blockpiece1 != blockpiece2)
				{
					BlockPath[blockpiece1 - 1].Red = -1;
				}
				break;
			case 2:
				if (PieceLocation[blockpiece1 - 1].Green == PieceLocation[blockpiece2 - 1].Green && blockpiece1 != blockpiece2)
				{
					BlockPath[blockpiece1 - 1].Green = -1;
				}
				break;
			case 3:
				if (PieceLocation[blockpiece1 - 1].Yellow == PieceLocation[blockpiece2 - 1].Yellow && blockpiece1 != blockpiece2)
				{
					BlockPath[blockpiece1 - 1].Yellow = -1;
				}
				break;
			case 4:
				if (PieceLocation[blockpiece1 - 1].Blue == PieceLocation[blockpiece2 - 1].Blue && blockpiece1 != blockpiece2)
				{
					BlockPath[blockpiece1 - 1].Blue = -1;
				}
				break;
			}
		}
	}
	PlayerCol(Player);
	printf(" Break the block.\n");
}

int CanMakeBlock(int roll)
{
	int block_piece = 0;
	for (int canmakepiece = 1; canmakepiece <= 4; canmakepiece++)
	{
		for (int otherpiece = 1; otherpiece <= 4; otherpiece++)
		{
			switch (Player) {
				case 1: {
					int maxloc = PieceLocation[canmakepiece - 1].Red + roll;
					int minloc = PieceLocation[canmakepiece - 1].Red - roll;
					if(maxloc > 51) {
						maxloc -= 51;
					}if	(minloc < 0) {
						minloc += 51;
					}
					if (maxloc == PieceLocation[otherpiece - 1].Red && canmakepiece != otherpiece && path[canmakepiece - 1].Red == 0)
					{
						block_piece = canmakepiece;
					}
					if (minloc == PieceLocation[otherpiece - 1].Red && canmakepiece != otherpiece && path[canmakepiece - 1].Red == 1)
					{
						block_piece = canmakepiece;
					}
					break;
				}
				case 2: {
					int maxloc = PieceLocation[canmakepiece - 1].Green + roll;
					int minloc = PieceLocation[canmakepiece - 1].Green - roll;
					if(maxloc > 51) {
						maxloc -= 51;
					}if	(minloc < 0) {
						minloc += 51;
					}
					if (maxloc == PieceLocation[otherpiece - 1].Green && canmakepiece != otherpiece && path[canmakepiece - 1].Green == 0)
					{
						block_piece = canmakepiece;
					}
					if (minloc == PieceLocation[otherpiece - 1].Green && canmakepiece != otherpiece && path[canmakepiece - 1].Green == 1)
					{
						block_piece = canmakepiece;
					}
					break;
				}
				case 3: {
					int maxloc = PieceLocation[canmakepiece - 1].Red + roll;
					int minloc = PieceLocation[canmakepiece - 1].Red - roll;
					if(maxloc > 51) {
						maxloc -= 51;
					}if	(minloc < 0) {
						minloc += 51;
					}
					if (maxloc == PieceLocation[otherpiece - 1].Yellow && canmakepiece != otherpiece && path[canmakepiece - 1].Yellow == 0)
					{
						block_piece = canmakepiece;
					}
					if (minloc == PieceLocation[otherpiece - 1].Yellow && canmakepiece != otherpiece && path[canmakepiece - 1].Yellow == 1)
					{
						block_piece = canmakepiece;
					}
					break;
				}
				case 4:{
					int maxloc = PieceLocation[canmakepiece - 1].Blue + roll;
				int minloc = PieceLocation[canmakepiece - 1].Blue - roll;
				if(maxloc > 51) {
					maxloc -= 51;
				}if	(minloc < 0) {
					minloc += 51;
				}
				if (maxloc == PieceLocation[otherpiece - 1].Blue && canmakepiece != otherpiece && path[canmakepiece - 1].Blue == 0)
				{
					block_piece = canmakepiece;
				}
				if (minloc == PieceLocation[otherpiece - 1].Blue && canmakepiece != otherpiece && path[canmakepiece - 1].Blue == 1)
				{
					block_piece = canmakepiece;
				}
				break;
			}
			}
		}
	}
	return block_piece;
}

int CanCapture(int roll)
{
	int cancapture = 0;
	for (int cappiece = 1; cappiece <= 4; cappiece++)
	{
		switch (Player)
		{
		case 1:
			if (BlockPath[cappiece - 1].Red == 0 && PieceLocation[cappiece - 1].Red >= 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red + (roll / block[PieceLocation[cappiece - 1].Red]);
					if(caploc > 51) {
						caploc -= 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue )
					{
						cancapture = cappiece;
					}
				}
			}else if (BlockPath[cappiece - 1].Red == 1 && PieceLocation[cappiece - 1].Red >= 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red - (roll / block[PieceLocation[cappiece - 1].Red]);
					if(caploc < 0) {
						caploc += 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue )
					{
						cancapture = cappiece;
					}
				}
			}else if (path[cappiece - 1].Red == 0 && PieceLocation[cappiece - 1].Red >= 0 && BlockPath[cappiece - 1].Red == -1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red + roll;
					if(caploc > 51) {
						caploc -= 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue )
					{
						cancapture = cappiece;
					}
				}
			}else if (path[cappiece - 1].Red == 1 && PieceLocation[cappiece - 1].Red >= 0 && BlockPath[cappiece - 1].Red == -1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red - roll;
					if(caploc < 0) {
						caploc += 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue )
					{
						cancapture = cappiece;
					}
				}
			}
			break;
		case 2:
			if (BlockPath[cappiece - 1].Green == 0 && PieceLocation[cappiece - 1].Green >= 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece -1 ].Green + (roll / block[PieceLocation[cappiece - 1].Green]);
					if(caploc > 51) {
						caploc -= 52;
					}
					if (caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}else if (BlockPath[cappiece - 1].Green == 1 && PieceLocation[cappiece - 1].Green >= 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Green - (roll / block[PieceLocation[cappiece - 1].Green]);
					if(caploc < 0) {
						caploc += 52;
					}
					if (caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}else if (path[cappiece - 1].Green == 0 && PieceLocation[cappiece - 1].Green >= 0 && BlockPath[cappiece - 1].Green == -1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece -1 ].Green + roll;
					if(caploc > 51) {
						caploc -= 52;
					}
					if (caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}else if (path[cappiece - 1].Green == 1 && PieceLocation[cappiece - 1].Green >= 0 && BlockPath[cappiece - 1].Green == -1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Green - roll;
					if(caploc < 0) {
						caploc += 52;
					}
					if (caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}
			break;
		case 3:
			if (BlockPath[cappiece - 1].Yellow == 0 && PieceLocation[cappiece - 1].Yellow >= 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++) {
					int caploc = PieceLocation[cappiece - 1].Yellow + (roll / block[PieceLocation[cappiece - 1].Yellow]);
					if(caploc > 51) {
						caploc -= 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}else if (BlockPath[cappiece - 1].Yellow == 1 && PieceLocation[cappiece - 1].Yellow >= 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Yellow - (roll / block[PieceLocation[cappiece - 1].Yellow]);
					if(caploc < 0) {
						caploc += 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}else if (path[cappiece - 1].Yellow == 0 && PieceLocation[cappiece - 1].Yellow >= 0 && BlockPath[cappiece - 1].Yellow == -1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Yellow + roll;
					if(caploc > 51) {
						caploc -= 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}else if (path[cappiece - 1].Yellow == 1 && PieceLocation[cappiece - 1].Yellow >= 0 && BlockPath[cappiece - 1].Yellow == -1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Yellow - roll;
					if(caploc < 0) {
						caploc += 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}
			break;
		case 4:
			if (BlockPath[cappiece - 1].Blue == 0 && PieceLocation[cappiece - 1].Blue >= 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Blue + (roll / block[PieceLocation[cappiece - 1].Blue]);
					if(caploc > 51) {
						caploc -= 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Red)
					{
						cancapture = cappiece;
					}
				}
			}else if (BlockPath[cappiece - 1].Blue == 1 && PieceLocation[cappiece - 1].Blue >= 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Blue - (roll / block[PieceLocation[cappiece - 1].Blue]);
					if(caploc < 0) {
						caploc += 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Red)
					{
						cancapture = cappiece;
					}
				}
			}else if (path[cappiece - 1].Blue == 0 && PieceLocation[cappiece - 1].Blue >= 0 && BlockPath[cappiece - 1].Blue == -1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Blue + roll;
					if(caploc > 51) {
						caploc -= 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Red)
					{
						cancapture = cappiece;
					}
				}
			}else if (path[cappiece - 1].Blue == 1 && PieceLocation[cappiece - 1].Blue >= 0 && BlockPath[cappiece - 1].Blue == -1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Blue - roll;
					if(caploc < 0) {
						caploc += 52;
					}
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Red)
					{
						cancapture = cappiece;
					}
				}
			}
			break;
		}
	}
	return cancapture;
}

void summury () {

	printf("Red player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", 4 - BasePiece.Red, BasePiece.Red);
	printf("Green player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", 4 - BasePiece.Green, BasePiece.Green);
	printf("Yellow player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", 4 - BasePiece.Yellow, BasePiece.Yellow);
	printf("Blue player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", 4 - BasePiece.Blue, BasePiece.Blue);
	printf("---------------------------------------\n");
	for( int i = 1; i <= 4; i++) {
		if(PieceLocation[i - 1].Red >= 0) {
			printf("Red R%d piece location %d.\n", i ,PieceLocation[i - 1].Red);
		}
	}
	printf("\n");
	for( int i = 1; i <= 4; i++) {
		if(PieceLocation[i - 1].Green >= 0) {
			printf("Green G%d piece location %d.\n", i ,PieceLocation[i - 1].Green);
		}
	}
	printf("\n");
	for( int i = 1; i <= 4; i++) {
		if(PieceLocation[i - 1].Yellow >= 0) {
			printf("Yellow Y%d piece location %d.\n", i ,PieceLocation[i - 1].Yellow);
		}
	}
	printf("\n");
	for( int i = 1; i <= 4; i++) {
		if(PieceLocation[i - 1].Blue >= 0) {
			printf("Blue B%d piece location %d.\n", i ,PieceLocation[i - 1].Blue);
		}
	}
	printf("---------------------------------------\n");
	printf("Red player has %d pieces at home.\n", GotHome.Red);
	printf("Green player has %d pieces at home.\n", GotHome.Green);
	printf("Yellow player has %d pieces at home.\n", GotHome.Yellow);
	printf("Blue player has %d pieces at home.\n", GotHome.Blue);
	printf("---------------------------------------\n");

}

void makeBlockX () {
	int count = 0, locationpiece;
	for( int pieceX = 1; pieceX <= 4; pieceX++) {
		switch (Player) {
			case 1:
				if (PieceLocation[pieceX - 1].Red == 26) {
					BlockPath[pieceX - 1].Red = 0;
					locationpiece = 26;
					count++;
				}
			break;
			case 2:
				if (PieceLocation[pieceX - 1].Green == 39) {
					BlockPath[pieceX - 1].Green = 0;
					count++;
					locationpiece = 39;
				}
			break;
			case 3:
				if (PieceLocation[pieceX - 1].Yellow == 0) {
					BlockPath[pieceX - 1].Yellow = 0;
					count++;
					locationpiece = 0;
				}
			break;
			case 4:
				if (PieceLocation[pieceX - 1].Blue == 13) {
					BlockPath[pieceX - 1].Blue = 0;
					count++;
					locationpiece = 13;
				}
			break;
		}
	}
	block[locationpiece] = count;
}

int piecepath (int location) {
	int returnpath = 1;
	if(block[location] == 1) {
		for (int piecex = 1; piecex <= 4; piecex++) {
			switch (Player) {
				case 1:
					if (PieceLocation[piecex - 1].Red == location && path[piecex - 1].Red == 1) {
						returnpath = 0;
					}
				break;
				case 2:
					if(PieceLocation[piecex - 1].Green == location && path[piecex - 1].Green == 1) {
						returnpath = 0;
					}
				break;
				case 3:
					if(PieceLocation[piecex - 1].Yellow == location && path[piecex - 1].Yellow == 1) {
						returnpath = 0;
					}
				case 4:
					if (PieceLocation[piecex - 1].Blue == location && path[piecex - 1].Blue == 1) {
						returnpath = 0;
					}
				break;
			}
		}
	} else if(block[location] > 1) {
		for (int piecex = 1; piecex <= 4; piecex++) {
			switch (Player) {
				case 1:
					if (PieceLocation[piecex - 1].Red == location && BlockPath[piecex - 1].Red == 1) {
						returnpath = 0;
					}
				break;
				case 2:
					if(PieceLocation[piecex - 1].Green == location && BlockPath[piecex - 1].Green == 1) {
						returnpath = 0;
					}
				break;
				case 3:
					if(PieceLocation[piecex - 1].Yellow == location && BlockPath[piecex - 1].Yellow == 1) {
						returnpath = 0;
					}
				case 4:
					if (PieceLocation[piecex - 1].Blue == location && BlockPath[piecex - 1].Blue == 1) {
						returnpath = 0;
					}
				break;
			}
		}
	}
	return returnpath;
}

void enterHomeStraight(int roll) {
    for (int piece = 1; piece <= 4; piece++) {
        int currentLocation, homeEntrance;
        int *pieceLocation, *capturedCount, *blockPath, *singlePath, *homePosition, *gothome;

        switch (Player) {
            case 1: // Red
                currentLocation = PieceLocation[piece - 1].Red;
                homeEntrance = 24;
                pieceLocation = &PieceLocation[piece - 1].Red;
                capturedCount = &captured[piece - 1].Red;
                blockPath = &BlockPath[piece - 1].Red;
                singlePath = &path[piece - 1].Red;
                homePosition = &Home[piece - 1].Red;
        		gothome = &GotHome.Red;
                break;
            case 2: // Green
                currentLocation = PieceLocation[piece - 1].Green;
                homeEntrance = 37;
                pieceLocation = &PieceLocation[piece - 1].Green;
                capturedCount = &captured[piece - 1].Green;
                blockPath = &BlockPath[piece - 1].Green;
                singlePath = &path[piece - 1].Green;
                homePosition = &Home[piece - 1].Green;
        		gothome = &GotHome.Green;
                break;
            case 3: // Yellow
                currentLocation = PieceLocation[piece - 1].Yellow;
                homeEntrance = 50;
                pieceLocation = &PieceLocation[piece - 1].Yellow;
                capturedCount = &captured[piece - 1].Yellow;
                blockPath = &BlockPath[piece - 1].Yellow;
                singlePath = &path[piece - 1].Yellow;
                homePosition = &Home[piece - 1].Yellow;
        		gothome = &GotHome.Yellow;
                break;
            case 4: // Blue
                currentLocation = PieceLocation[piece - 1].Blue;
                homeEntrance = 11;
                pieceLocation = &PieceLocation[piece - 1].Blue;
                capturedCount = &captured[piece - 1].Blue;
                blockPath = &BlockPath[piece - 1].Blue;
                singlePath = &path[piece - 1].Blue;
                homePosition = &Home[piece - 1].Blue;
        		gothome = &GotHome.Blue;
                break;
        }

        if (*capturedCount < 1 || *pieceLocation < 0) continue;

        int stepsToMove = roll / block[currentLocation];
        int canEnter = 0;

        if (*singlePath == 0 && *blockPath == -1) { // Clockwise single piece movement
            for (int i = 1; i <= roll; i++) {
                int nextLocation = (currentLocation + i) % 52;
                if (block[nextLocation] > 1 && nextLocation != homeEntrance) {
                    stepsToMove = i - 1;
                    break;
                }
            }
            canEnter = ((currentLocation + stepsToMove) % 52 >= homeEntrance);
        } else if (*blockPath == 0) { // Clockwise block movement
        	for (int i = 1; i <= stepsToMove; i++) {
        		int nextLocation = (currentLocation + i) % 52;
        		if (block[nextLocation] > block[currentLocation] && nextLocation != homeEntrance) {
        			stepsToMove = i - 1;
        			break;
        		}
        	}
        	canEnter = ((currentLocation + stepsToMove) % 52 >= homeEntrance);
        }else if (*singlePath == 1 && *blockPath == -1){ // Counterclockwise single piece movement
            for (int i = 1; i <= roll; i++) {
                int nextLocation = (currentLocation - i + 52) % 52;
                if (block[nextLocation] > 1 && nextLocation != homeEntrance) {
                    stepsToMove = i - 1;
                    break;
                }
            }
            int distanceFromHome = (homeEntrance - currentLocation + 52) % 52;
            canEnter = (distanceFromHome <= stepsToMove);
        }else if (*blockPath == 1){ // Counterclockwise block movement
        	for (int i = 1; i <= stepsToMove; i++) {
        		int nextLocation = (currentLocation - i + 52) % 52;
        		if (block[nextLocation] > block[currentLocation] && nextLocation != homeEntrance) {
        			stepsToMove = i - 1;
        			break;
        		}
        	}
        	int distanceFromHome = (homeEntrance - currentLocation + 52) % 52;
        	canEnter = (distanceFromHome <= stepsToMove);
        }

        if (canEnter) {
            int stepsIntoHomeStraight;
            if (*singlePath == 0 && *blockPath == -1) {
                stepsIntoHomeStraight = ((currentLocation + stepsToMove) % 52) - homeEntrance + 1;
            } else if (*blockPath == 0) {
            	stepsIntoHomeStraight = ((currentLocation + stepsToMove) % 52) - homeEntrance + 1;
            }else if (*singlePath == 1 && *blockPath == -1){
                stepsIntoHomeStraight = stepsToMove - ((homeEntrance - currentLocation + 52) % 52) + 1;
            }else{
            	stepsIntoHomeStraight = stepsToMove - ((homeEntrance - currentLocation + 52) % 52) + 1;
            }

            *homePosition = (stepsIntoHomeStraight > 6) ? 6 : stepsIntoHomeStraight;
            *pieceLocation = -20; // Indicate that the piece is in home straight

            if (block[currentLocation] > 1) {
                *blockPath = 0; // Reset block path as the piece is no longer part of a block
            }
            block[currentLocation] = 0;

        	PlayerCol(Player);
            printf(" piece %d enters the home straight and moves to position %d\n", piece, *homePosition);

            if (*homePosition == 6) {
                printf("Player %d's piece %d has reached home!\n", Player, piece);
                *homePosition = -1; // Remove from home straight
            	*gothome++;

            }

            break; // Exit the loop after moving a piece
        }
    }
}