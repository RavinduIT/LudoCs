#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "logic.h"

int Player;
int SixInRow;

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
	}
}

void intro()
{
	printf("The red player has four (04) pieces named R1, R2, R3, and R4.\n");
	printf("The green player has four (04) pieces named G1, G2, G3, and G4.\n");
	printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
	printf("The blue player has four (04) pieces named B1, B2, B3, and B4\n");
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
		if(location == 52)
		location = 0;
		else if(location == 53)
		location = 1;
		else if(location == 54)
		location = 2;
		else if(location == 55)
		location = 3;
		else if(location == 56)
		location = 4;
		else if(location == 57)
		location = 5;
	}
	int returnval = 0;
	if (block[location] > 0)
	{
		int move = 0, hadablock = 0;
		move = roll / block[location];
		int havetojump = move;

		for (int otherblock = (location + 1); otherblock <= (location + move); otherblock++)
		{
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
									block[location]--;
									block[location + move]++;
									printf("R%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Red == 1)
								{
									PieceLocation[locpiece - 1].Red -= move;
									block[location]--;
									block[location - move]++;
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
									block[location]--;
									block[location + move]++;
									printf("G%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Green == 1)
								{
									PieceLocation[locpiece - 1].Green -= move;
									block[location]--;
									block[location - move]++;
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
									block[location]--;
									block[location + move]++;
									printf("Y%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Yellow == 1)
								{
									PieceLocation[locpiece - 1].Yellow -= move;
									block[location]--;
									block[location - move]++;
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
									block[location]--;
									block[location + move]++;
									printf("B%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Blue == 1)
								{
									PieceLocation[locpiece - 1].Blue -= move;
									block[location]--;
									block[location - move]++;
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
					return 10;
				}

				else if (block[location] == 1)
				{
					PlayerCol(Player);
					printf(" piece ");
					for (int movepiece = 1; movepiece <= 4; movepiece++)
					{
						switch (Player)
						{
						case 1:
							if (PieceLocation[movepiece - 1].Red == location)
							{
								if (path[movepiece - 1].Red == 0)
								{
									PieceLocation[movepiece - 1].Red += move;
									block[location] = 0;
									block[location + move]++;
									printf("R%d ", movepiece);
								}
								else if (BlockPath[movepiece - 1].Red == 1)
								{
									PieceLocation[movepiece - 1].Red -= move;
									block[location] = 0;
									block[location - move]++;
									printf("R%d ", movepiece);
								}
							}
							break;
						case 2:
							if (PieceLocation[movepiece - 1].Green == location)
							{
								if (path[movepiece - 1].Green == 0)
								{
									PieceLocation[movepiece - 1].Green += move;
									block[location] = 0;
									block[location + move]++;
									printf("G%d ", movepiece);
								}
								else if (BlockPath[movepiece - 1].Green == 1)
								{
									PieceLocation[movepiece - 1].Green -= move;
									block[location] = 0;
									block[location - move]++;
									printf("G%d ", movepiece);
								}
							}
							break;
						case 3:
							if (PieceLocation[movepiece - 1].Yellow == location)
							{
								if (path[movepiece - 1].Yellow == 0)
								{
									PieceLocation[movepiece - 1].Yellow += move;
									block[location] = 0;
									block[location + move]++;
									printf("Y%d ", movepiece);
								}
								else if (BlockPath[movepiece - 1].Yellow == 1)
								{
									PieceLocation[movepiece - 1].Yellow -= move;
									block[location] = 0;
									block[location - move]++;
									printf("Y%d ", movepiece);
								}
							}
							break;
						case 4:
							if (PieceLocation[movepiece - 1].Blue == location)
							{
								if (path[movepiece - 1].Blue == 0)
								{
									PieceLocation[movepiece - 1].Blue += move;
									block[location] = 0;
									block[location + move]++;
									printf("B%d ", movepiece);
								}
								else if (BlockPath[movepiece - 1].Blue == 1)
								{
									PieceLocation[movepiece - 1].Blue -= move;
									block[location] = 0;
									block[location - move]++;
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

		}
		if (hadablock == 0)
			{
				int newpiecelocation = 0;
				PlayerCol(Player);
				printf(" moves piece ");
				if (block[location] == 1)
				{
					for (int movepiece = 1; movepiece <= 4; movepiece++)
					{
						switch (Player)
						{
						case 1:
							if (PieceLocation[movepiece - 1].Red == location)
							{
								if (path[movepiece - 1].Red == 0)
								{
									PieceLocation[movepiece - 1].Red += move;
									block[location] = 0;
									block[location + move]++;
									newpiecelocation = location + move;
									printf("R%d ", movepiece);
								}
								else if (BlockPath[movepiece - 1].Red == 1)
								{
									PieceLocation[movepiece - 1].Red -= move;
									block[location] = 0;
									block[location - move]++;
									newpiecelocation = location - move;
									printf("R%d ", movepiece);
								}
							}
							break;
						case 2:
							if (PieceLocation[movepiece - 1].Green == location)
							{
								if (path[movepiece - 1].Green == 0)
								{
									PieceLocation[movepiece - 1].Green += move;
									block[location] = 0;
									block[location + move]++;
									newpiecelocation = location + move;
									printf("G%d ", movepiece);
								}
								else if (BlockPath[movepiece - 1].Green == 1)
								{
									PieceLocation[movepiece - 1].Green -= move;
									block[location] = 0;
									block[location - move]++;
									newpiecelocation = location - move;
									printf("G%d ", movepiece);
								}
							}
							break;
						case 3:
							if (PieceLocation[movepiece - 1].Yellow == location)
							{
								if (path[movepiece - 1].Yellow == 0)
								{
									PieceLocation[movepiece - 1].Yellow += move;
									block[location] = 0;
									block[location + move]++;
									newpiecelocation = location + move;
									printf("Y%d ", movepiece);
								}
								else if (BlockPath[movepiece - 1].Yellow == 1)
								{
									PieceLocation[movepiece - 1].Yellow -= move;
									block[location] = 0;
									block[location - move]++;
									newpiecelocation = location - move;
									printf("Y%d ", movepiece);
								}
							}
							break;
						case 4:
							if (PieceLocation[movepiece - 1].Blue == location)
							{
								if (path[movepiece - 1].Blue == 0)
								{
									PieceLocation[movepiece - 1].Blue += move;
									block[location] = 0;
									block[location + move]++;
									newpiecelocation = location + move;
									printf("B%d ", movepiece);
								}
								else if (BlockPath[movepiece - 1].Blue == 1)
								{
									PieceLocation[movepiece - 1].Blue -= move;
									block[location] = 0;
									block[location - move]++;
									newpiecelocation = location - move;
									printf("B%d ", movepiece);
								}
							}
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
					return 0;
				}
				else if (block[location] > 1)
				{
					for (int locpiece = 1; locpiece <= 4; locpiece++)
					{
						switch (Player)
						{
						case 1:
							if (PieceLocation[locpiece - 1].Red == location)
							{
								if (path[locpiece - 1].Red == 0)
								{
									PieceLocation[locpiece - 1].Red += move;
									block[location]--;
									block[location + move]++;
									newpiecelocation = location + move;
									printf("R%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Red == 1)
								{
									PieceLocation[locpiece - 1].Red -= move;
									block[location]--;
									block[location - move]++;
									newpiecelocation = location - move;
									printf("R%d, ", locpiece);
								}
							}
							break;
						case 2:
							if (PieceLocation[locpiece - 1].Green == location)
							{
								if (path[locpiece - 1].Green == 0)
								{
									PieceLocation[locpiece - 1].Green += move;
									block[location]--;
									block[location + move]++;
									newpiecelocation = location + move;
									printf("G%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Green == 1)
								{
									PieceLocation[locpiece - 1].Green -= move;
									block[location]--;
									block[location - move]++;
									newpiecelocation = location - move;
									printf("G%d, ", locpiece);
								}
							}
							break;
						case 3:
							if (PieceLocation[locpiece - 1].Yellow == location)
							{
								if (path[locpiece - 1].Yellow == 0)
								{
									PieceLocation[locpiece - 1].Yellow += move;
									block[location]--;
									block[location + move]++;
									newpiecelocation = location + move;
									printf("Y%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Yellow == 1)
								{
									PieceLocation[locpiece - 1].Yellow -= move;
									block[location]--;
									block[location - move]++;
									newpiecelocation = location - move;
									printf("Y%d, ", locpiece);
								}
							}
							break;
						case 4:
							if (PieceLocation[locpiece - 1].Blue == location)
							{
								if (path[locpiece - 1].Blue == 0)
								{
									PieceLocation[locpiece - 1].Blue += move;
									block[location]--;
									block[location + move]++;
									newpiecelocation = location + move;
									printf("B%d, ", locpiece);
								}
								else if (BlockPath[locpiece - 1].Blue == 1)
								{
									PieceLocation[locpiece - 1].Blue -= move;
									block[location]--;
									block[location - move]++;
									newpiecelocation = location - move;
									printf("B%d, ", locpiece);
								}
							}
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
	if(location > 51) {
		location %= 52;
	}
	return returnval;
}

void BaseToBoard()
{
	switch (Player)
	{
	case 1:
		for (int i = 1; i <= 4; i++)
		{
			if (Piecelocation(1, i) == -10)
			{
				BasePiece.Red--;
				printf("Red player moves piece R%d to the starting point.\n", i);
				printf("Red player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Red), BasePiece.Red);
				PieceLocation[i - 1].Red = 26;
				block[26]++;
				HeadTail(i);
				break;
			}
		}
		break;
	case 2:
		for (int i = 1; i <= 4; i++)
		{
			if (Piecelocation(2, i) == -10)
			{
				BasePiece.Green--;
				printf("Green player moves piece G%d to the starting point.\n", i);
				printf("Green player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Green), BasePiece.Green);
				PieceLocation[i - 1].Green = 39;
				block[39]++;
				HeadTail(i);
				break;
			}
		}
		break;
	case 3:
		for (int i = 1; i <= 4; i++)
		{
			if (Piecelocation(3, i) == -10)
			{
				BasePiece.Yellow--;
				printf("Yellow player moves piece Y%d to the starting point.\n", i);
				printf("Yellow player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Yellow), BasePiece.Yellow);
				PieceLocation[i - 1].Yellow = 0;
				block[0]++;
				HeadTail(i);
				break;
			}
		}
		break;
	case 4:
		for (int i = 1; i <= 4; i++)
		{
			if (Piecelocation(4, i) == -10)
			{
				BasePiece.Blue--;
				printf("Blue player moves piece B%d to the starting point.\n", i);
				printf("Blue player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Blue), BasePiece.Blue);
				PieceLocation[i - 1].Blue = 13;
				block[13]++;
				HeadTail(i);
				break;
			}
		}
		break;
	}
}

int Piecelocation(int player, int piece)
{
	int location = 0;
	switch (player)
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

void Capture(int piece, int roll)
{
	int Basepiece = 0;
	int location = Piecelocation(Player, piece);
	int newlocation = location + roll;

	switch (Player)
	{
	case 1:
		printf("Red piece ");
		for (int p = 1; p <= 4; p++)
		{
			if (PieceLocation[p - 1].Red == location)
			{
				Move(location, PieceLocation[p - 1].Red);
				printf("R%d, ", p);
				captured[p - 1].Red++;
			}
		}
		printf("lands on square L%d, captures ", newlocation);
		break;

	case 2:
		printf("Green piece ");
		for (int p = 1; p <= 4; p++)
		{
			if (PieceLocation[p - 1].Green == newlocation)
			{
				Move(location, PieceLocation[p - 1].Green);
				printf("G%d, ", p);
				captured[p - 1].Green++;
			}
		}
		printf("lands on square L%d, captures ", newlocation);
		break;

	case 3:
		printf("Yellow piece ");
		for (int p = 1; p <= 4; p++)
		{
			if (PieceLocation[p - 1].Yellow == newlocation)
			{
				Move(location, PieceLocation[p - 1].Yellow);
				printf("Y%d, ", p);
				captured[p - 1].Yellow++;
			}
		}
		printf("lands on square L%d, captures ", location);
		break;

	case 4:
		printf("piece ");
		for (int p = 1; p <= 4; p++)
		{
			if (PieceLocation[p - 1].Blue == newlocation)
			{
				Move(location, PieceLocation[p - 1].Blue);
				printf("B%d, ", p);
				captured[p - 1].Blue++;
			}
		}
		printf("lands on square L%d, captures ", newlocation);
		break;
	}
	int capplayer = 0;
	for (capplayer = 1; capplayer <= 4; capplayer++)
	{
		if (newlocation == Piecelocation(capplayer, 1) || newlocation == Piecelocation(capplayer, 2) || newlocation == Piecelocation(capplayer, 3) || newlocation == Piecelocation(capplayer, 4))
		{
			PlayerCol(capplayer);
			for (int cappiece = 1; cappiece <= 4; cappiece++)
			{
				if (Piecelocation(capplayer, cappiece) == newlocation && capplayer != Player)
				{
					switch (capplayer)
					{
					case 1:
						printf("R%d", cappiece);
						break;
					case 2:
						printf("G%d, ", cappiece);
						break;
					case 3:
						printf("Y%d, ", cappiece);
						break;
					case 4:
						printf("B%d, ", cappiece);
						break;
					}
				}
			}
		}
		printf("Return it to the base.\n");
		Reset(newlocation);
		Move(location, roll);
		PlayerCol(capplayer);
		switch (capplayer)
		{
		case 1:
			Basepiece = BasePiece.Red;
			break;
		case 2:
			Basepiece = BasePiece.Green;
			break;
		case 3:
			Basepiece = BasePiece.Yellow;
			break;
		case 4:
			Basepiece = BasePiece.Blue;
			break;
		}
	}
	printf("player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - Basepiece), Basepiece);
}

void Reset(int location)
{
    for (int r = 0; r <= 4; r++)
    {
        switch (r)
        {
        case 1:
            for (int s = 1; s <= 4; s++)
            {
                if (PieceLocation[s - 1].Red == location)
                {
                    PieceLocation[s - 1].Red = -10;
                    captured[s - 1].Red = 0;
                    BasePiece.Red++;
                    path[s - 1].Red = -1;
                }
            }
            break; 
        case 2:
            for (int s = 1; s <= 4; s++)
            {
                if (PieceLocation[s - 1].Green == location)
                {
                    PieceLocation[s - 1].Green = -10;
                    captured[s - 1].Green = 0;
                    BasePiece.Green++;
                    path[s - 1].Green = -1;
                }
            }
            break; 
        case 3:
            for (int s = 1; s <= 4; s++)
            {
                if (PieceLocation[s - 1].Yellow == location)
                {
                    PieceLocation[s - 1].Yellow = -10;
                    captured[s - 1].Yellow = 0;
                    BasePiece.Yellow++;
                    path[s - 1].Yellow = -1;
                }
            }
            break; 
        case 4:
            for (int s = 1; s <= 4; s++)
            {
                if (PieceLocation[s - 1].Blue == location)
                {
                    PieceLocation[s - 1].Blue = -10;
                    captured[s - 1].Blue = 0;
                    BasePiece.Blue++;
                    path[s - 1].Blue = -1;
                }
            }
            break; 
        }
    }
}

void AI(int roll)
{
	if (SixInRow > 2)
	{
		PlayerCol(Player);
		printf(" six rolled for the third consecutive time, the roll is ignored.\n");
		BreakBlock();
		return;
	}

	switch (Player)
	{

	case 1: {
		int cancapture[4] = {55, 55, 55, 55};
		int minval = 55;
		int choosepiece = 0;
		for (int c = 1; c <= 4; c++)
		{
			int location = (PieceLocation[c - 1].Red + roll);
			for (int d = 1; d <= 4; d++)
			{
				if ((location == PieceLocation[d - 1].Green || location == PieceLocation[d - 1].Yellow || location == PieceLocation[d - 1].Blue) && (block[location - roll] >= block[location]))
				{
					if (path[c - 1].Red == 0)
					{
						cancapture[c - 1] = (50 - location);
						break;
					}
					if (path[c - 1].Red == 1)
					{
						cancapture[c - 1] = location + 2;
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
			if (roll == 6)
			{
				SixInRow++;
			}
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}

		else if (roll == 6 && SixInRow <= 2 && BasePiece.Red > 0 && SixInRow <= 2)
		{ // Red move a piece base to board
			BaseToBoard();
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			SixInRow++;
			AI(roll);
		}
		else if (SixInRow <= 2 && BasePiece.Red < 4) {
			int PossibleMove = 0;
			for (int y = 1; y <= 4; y++)
			{
				for (int Piecerd = 1; Piecerd <= 4; Piecerd++)
				{
					if ((PieceLocation[Piecerd - 1].Red != (PieceLocation[y - 1].Red + roll)) && (y != Piecerd) && PieceLocation[Piecerd - 1].Red >= 0)
					{ // Move Red piece but avoid making block
						Move(PieceLocation[y - 1].Red, roll);
						PossibleMove++;
						if (roll == 6)
						{
							SixInRow++;
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
						SixInRow++;
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
				SixInRow++;
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
			}

		else if (roll == 6 && BasePiece.Green > 0)
		{
			BaseToBoard();
			SixInRow++;
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}
		else
		{
			int randompiecelocation = 0, piecehavetomove = 0, isitblocked = 0;
			for (int loop = 1; loop <= 4; loop++) {
				randompiecelocation = PieceLocation[loop - 1].Green;
				if (block[randompiecelocation] >= 1)
				{
					piecehavetomove = loop;
				}
			}
				isitblocked = Move(PieceLocation[piecehavetomove - 1].Green, roll);
				if (isitblocked == 10)
				{
					BreakBlock();
				}
				if (roll == 6)
				{
					SixInRow++;
					roll = Roll();
					PlayerCol(Player);
					printf(" player rolled %d.\n", roll);
					AI(roll);
			}
		}
		SixInRow = 0;
		break;
	}
	case 3:
		if (roll == 6 && BasePiece.Yellow > 0)
		{
			BaseToBoard();
			SixInRow++;
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}
		else
		{
			int cancapture = CanCapture(roll);
			if (cancapture > 0)
			{
				Capture(cancapture, roll);
				if (roll == 6)
				{
					SixInRow++;
					roll = Roll();
					PlayerCol(Player);
					printf(" player rolled %d.\n", roll);
					AI(roll);
				}
			}
			else
			{
				int thepiece = 0;

				for (int closetohome = 1; closetohome <= 4; closetohome++)
				{
					int hometolocation = 55;
					if (path[closetohome - 1].Yellow == 0)
					{
						if (hometolocation > (52 - PieceLocation[closetohome - 1].Yellow) && PieceLocation[closetohome - 1].Yellow > 0 )
						{
							thepiece = closetohome;
						}
					}
					else if (path[closetohome - 1].Yellow == 1)
					{
						if (hometolocation > (2 + PieceLocation[closetohome - 1].Yellow) && PieceLocation[closetohome - 1].Yellow > 0)
						{
							thepiece = closetohome;
						}
					}
				}
				if (thepiece > 0)
				{
					Move(PieceLocation[thepiece - 1].Yellow, roll);
					if (roll == 6)
					{
						SixInRow++;
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

	block[currentlocation % 52] = 0;
	block[(currentlocation + roll) % 52] += oldblock;
	for (int newpiece = 1; newpiece <= 4; newpiece++)
	{
		switch (Player)
		{
		case 1:
			if (PieceLocation[newpiece - 1].Red == (currentlocation + roll))
			{
				newpiecepath = path[newpiece - 1].Red;
			}
			oldpiecepath = path[piece-1].Red;
			break;
		case 2:
			if (PieceLocation[newpiece - 1].Green == (currentlocation + roll))
			{
				newpiecepath = path[newpiece - 1].Green;
			} //  to get new location piece path
			oldpiecepath = path[piece - 1].Green;
			break;
		case 3:
			if (PieceLocation[newpiece - 1].Yellow == (currentlocation + roll))
			{
				newpiecepath = path[newpiece- 1 ].Yellow;
			}
			oldpiecepath = path[piece - 1].Yellow;
			break;
		case 4:
			if (PieceLocation[newpiece - 1].Blue == (currentlocation + roll))
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
			hometooldpiece = 50 - currentlocation + roll; // to get path of the block
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

	block[(currentlocation + roll) % 52] += oldblock;
	Move(currentlocation, roll);
}

void HeadTail(int piece)
{

	int headtail = ((rand() % 2));   //  0 = clockwise  1 = counterwise.
	switch (Player)
	{
	case 1:
		path[piece].Red = headtail;
		break;
	case 2:
		path[piece].Green = headtail;
		break;
	case 3:
		path[piece].Yellow = headtail;
		break;
	case 4:
		path[piece].Blue = headtail;
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
		for (int blockpiece2 = 1; blockpiece2 <= 4; blockpiece2++)
		{
			switch (Player)
			{
			case 1:
				if (PieceLocation[blockpiece1 - 1].Red == PieceLocation[blockpiece2 - 1].Red && blockpiece1 != blockpiece2)
				{
					int breakblocklocation = PieceLocation[blockpiece1 - 1].Red;
					block[breakblocklocation] = 1;
				}
				break;
			case 2:
				if (PieceLocation[blockpiece1 - 1].Green == PieceLocation[blockpiece2 - 1].Green && blockpiece1 != blockpiece2)
				{
					int breakblocklocation = PieceLocation[blockpiece1 - 1].Green;
					block[breakblocklocation] = 1;
				}
				break;
			case 3:
				if (PieceLocation[blockpiece1 - 1].Yellow == PieceLocation[blockpiece2 - 1].Yellow && blockpiece1 != blockpiece2)
				{
					int breakblocklocation = PieceLocation[blockpiece1 - 1].Yellow;
					block[breakblocklocation] = 1;
				}
				break;
			case 4:
				if (PieceLocation[blockpiece1 - 1].Blue == PieceLocation[blockpiece2 - 1].Blue && blockpiece1 != blockpiece2)
				{
					int breakblocklocation = PieceLocation[blockpiece1 - 1].Blue;
					block[breakblocklocation] = 1;
				}
				break;
			}
		}
	}
	PlayerCol(Player);
	printf(" Break the block.");
}

int CanMakeBlock(int roll)
{
	int block_piece = 0;
	for (int canmakepiece = 1; canmakepiece <= 4; canmakepiece++)
	{
		for (int otherpiece = 1; otherpiece <= 4; otherpiece++)
		{
			switch (Player)
			{
			case 1:
				if ((PieceLocation[canmakepiece - 1].Red + roll) == PieceLocation[otherpiece - 1].Red && canmakepiece != otherpiece)
				{
					block_piece = canmakepiece;
				}
			case 2:
				if ((PieceLocation[canmakepiece - 1].Green + roll) == PieceLocation[otherpiece - 1].Green && canmakepiece != otherpiece)
				{
					block_piece = canmakepiece;
				}
			case 3:
				if ((PieceLocation[canmakepiece - 1].Yellow + roll) == PieceLocation[otherpiece - 1].Yellow && canmakepiece != otherpiece)
				{
					block_piece = canmakepiece;
				}
			case 4:
				if ((PieceLocation[canmakepiece - 1].Blue + roll) == PieceLocation[otherpiece - 1].Blue && canmakepiece != otherpiece)
				{
					block_piece = canmakepiece;
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
			if (path->Red == 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red + roll;
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}
			if (path->Red == 1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red - roll;
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}
			break;
		case 2:
			if (path->Green == 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece -1 ].Green + roll;
					if (caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}
			if (path->Green == 1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Green - roll;
					if (caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}
			break;
		case 3:
			if (path->Yellow == 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Yellow + roll;
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}
			if (path->Yellow == 1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Yellow - roll;
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue)
					{
						cancapture = cappiece;
					}
				}
			}
			break;
		case 4:
			if (path->Blue == 0)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Blue + roll;
					if (caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Red)
					{
						cancapture = cappiece;
					}
				}
			}
			if (path->Blue == 1)
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Blue - roll;
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