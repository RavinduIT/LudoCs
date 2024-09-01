
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "logic.h"

int Player;  // current player
int SixInRow; // Roll 6 in row times
int bluepiece;  // current blue player

void SetValues()												// set all the values at starting point
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
{                                                              // Print the colour of the player
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
	return ((rand() % 6) + 1);									// get a value between 1 - 6 for Roll dice
}

void ChooseFirstPlayer()
{																// Select a player who first to move
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
			maxplayer = 1;										// select the player who rolled highest
		}
		PlayerCol(maxplayer);
		maxplayer++;
	}
	Player = maxplayer;
	printf(".\n");
}

int Move(int location, int roll)
{
	if (block[location] > 0)
	{
		int move = 0, hadablock = 0;
		int havetojump = move;
		int otherblock = 0;
		short thepath = piecepath(location);
		move = roll / block[location];
		if (thepath == 0)
		{
			otherblock = location + 1;
		}
		else
		{
			otherblock = location - 1;
		}
		if (move == 0)
		{
			return 0;
		}
		for (int run4times = 1; run4times <= move; run4times++)
		{
			otherblock = (otherblock + 52) % 52;
			if (block[otherblock] > block[location]) 										// check if there are any block infront of the piece/block
			{

				hadablock = 1;
				if (move >= abs(otherblock - location))
				{
					move = abs(otherblock - location) - 1;
					if (move > 6)
					{
						move = 51 - move;
					}
				}
				int can_canpture = CanCapture(roll);                  						 //	Capture if can capture 
				if (can_canpture)
				{
					CanCapture(move);
					break;
				}
				if (move == 0)
				{
					PlayerCol(Player);
					printf(" is blocked from moving from L%d to L%d by", location, otherblock);
					return 0;
				}
				if (block[location] > 1)
				{
					PlayerCol(Player);
					printf(" pieces ");
					for (int locpiece = 1; locpiece <= 4; locpiece++)
					{
						switch (Player)
						{
						case 1:
							if (PieceLocation[locpiece - 1].Red == location) 				// Red block move if there's a block infront of it
							{			
								if (BlockPath[locpiece - 1].Red == 0)
								{
									PieceLocation[locpiece - 1].Red += move;
									if (PieceLocation[locpiece - 1].Red > 51)
									{
										PieceLocation[locpiece - 1].Red -= 52;
										block[location]--;
										block[(location + move) - 52]++;
									}
									else
									{
										block[location]--;
										block[location + move]++;
									}
									printf("R%d, ", locpiece);
									havetojump += PieceLocation[locpiece - 1].Red;
								}
								else if (BlockPath[locpiece - 1].Red == 1)
								{
									PieceLocation[locpiece - 1].Red -= move;
									if (PieceLocation[locpiece - 1].Red < 0)
									{
										PieceLocation[locpiece - 1].Red += 52;
										block[location]--;
										block[(location - move) + 52]++;
									}
									else
									{
										block[location]--;
										block[location - move]++;
									}
									printf("R%d, ", locpiece);
									havetojump = PieceLocation[locpiece - 1].Red - havetojump;
								}
							}
							break;
						case 2:
							if (PieceLocation[locpiece - 1].Green == location) 					// Green block move if there's a block infront of it
							{
								if (BlockPath[locpiece - 1].Green == 0)
								{
									PieceLocation[locpiece - 1].Green += move;
									if (PieceLocation[locpiece - 1].Green > 51)
									{
										PieceLocation[locpiece - 1].Green -= 52;
										block[location]--;
										block[(location + move) - 52]++;
									}
									else
									{
										block[location]--;
										block[location + move]++;
									}
									printf("G%d, ", locpiece);
									havetojump += PieceLocation[locpiece - 1].Green;
								}
								else if (BlockPath[locpiece - 1].Green == 1)
								{
									PieceLocation[locpiece - 1].Green -= move;
									if (PieceLocation[locpiece - 1].Green < 0)
									{
										PieceLocation[locpiece - 1].Green += 52;
										block[location]--;
										block[(location - move) + 52]++;
									}
									else
									{
										block[location]--;
										block[location - move]++;
									}
									printf("G%d, ", locpiece);
									havetojump = PieceLocation[locpiece - 1].Green - havetojump;
								}
							}
							break;
						case 3:
							if (PieceLocation[locpiece - 1].Yellow == location)						 // Yellow block move if there's a block infront of it
							{
								if (BlockPath[locpiece - 1].Yellow == 0)
								{
									PieceLocation[locpiece - 1].Yellow += move;
									if (PieceLocation[locpiece - 1].Yellow > 51)
									{
										PieceLocation[locpiece - 1].Yellow -= 52;
										block[location]--;
										block[(location + move) - 52]++;
									}
									else
									{
										block[location]--;
										block[location + move]++;
									}
									printf("Y%d, ", locpiece);
									havetojump += PieceLocation[locpiece - 1].Yellow;
								}
								else if (BlockPath[locpiece - 1].Yellow == 1)
								{
									PieceLocation[locpiece - 1].Yellow -= move;
									if (PieceLocation[locpiece - 1].Yellow < 0)
									{
										PieceLocation[locpiece - 1].Yellow += 52;
										block[location]--;
										block[(location - move) + 52]++;
									}
									else
									{
										block[location]--;
										block[location - move]++;
									}
									printf("Y%d, ", locpiece);
									havetojump = PieceLocation[locpiece - 1].Yellow - havetojump;
								}
							}
							break;
						case 4:
							if (PieceLocation[locpiece - 1].Blue == location) 					// Blue block move if there's a block infront of it
							{
								if (BlockPath[locpiece - 1].Blue == 0)
								{
									PieceLocation[locpiece - 1].Blue += move;
									if (PieceLocation[locpiece - 1].Blue > 51)
									{
										PieceLocation[locpiece - 1].Blue -= 52;
										block[location]--;
										block[(location + move) - 52]++;
									}
									else
									{
										block[location]--;
										block[location + move]++;
									}
									printf("B%d, ", locpiece);
									havetojump += PieceLocation[locpiece - 1].Blue;
								}
								else if (BlockPath[locpiece - 1].Blue == 1)
								{
									PieceLocation[locpiece - 1].Blue -= move;
									if (PieceLocation[locpiece - 1].Blue < 0)
									{
										PieceLocation[locpiece - 1].Blue += 52;
										block[location]--;
										block[(location - move) + 52]++;
									}
									else
									{
										block[location]--;
										block[location - move]++;
									}
									printf("B%d, ", locpiece);
									havetojump = PieceLocation[locpiece - 1].Blue - havetojump;
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
							if (PieceLocation[movepiece - 1].Red == location) 				// Red piece move if there's a block infront of it
							{
								moved = 1;
								if (path[movepiece - 1].Red == 0 && BlockPath[movepiece - 1].Red == -1)
								{
									PieceLocation[movepiece - 1].Red += move;
									if (PieceLocation[movepiece - 1].Red > 51)
									{
										PieceLocation[movepiece - 1].Red -= 52;
										block[location]--;
										block[(location + move) - 52]++;
									}
									else
									{
										block[location]--;
										block[location + move]++;
									}
									printf("R%d ", movepiece);
									havetojump = PieceLocation[movepiece - 1].Red + havetojump;
								}
								else if (path[movepiece - 1].Red == 1 && BlockPath[movepiece - 1].Red == -1)
								{
									PieceLocation[movepiece - 1].Red -= move;
									if (PieceLocation[movepiece - 1].Red < 0)
									{
										PieceLocation[movepiece - 1].Red += 52;
										block[location]--;
										block[(location - move) + 52]++;
									}
									else
									{
										block[location]--;
										block[location - move]++;
									}
									printf("R%d ", movepiece);
									havetojump = PieceLocation[movepiece - 1].Red - havetojump;
								}
							}
							break;
						case 2:
							if (PieceLocation[movepiece - 1].Green == location)					 // Green piece move if there's a block infront of it
							{
								moved = 1;
								if (path[movepiece - 1].Green == 0 && BlockPath[movepiece - 1].Green == -1)
								{
									PieceLocation[movepiece - 1].Green += move;
									if (PieceLocation[movepiece - 1].Green > 51)
									{
										PieceLocation[movepiece - 1].Green -= 52;
										block[location]--;
										block[(location + move) - 52]++;
									}
									else
									{
										block[location]--;
										block[location + move]++;
									}
									printf("G%d ", movepiece);
									havetojump = PieceLocation[movepiece - 1].Green - havetojump;
								}
								else if (path[movepiece - 1].Green == 1 && BlockPath[movepiece - 1].Green == -1)
								{
									PieceLocation[movepiece - 1].Green -= move;
									if (PieceLocation[movepiece - 1].Green < 0)
									{
										PieceLocation[movepiece - 1].Green += 52;
										block[location]--;
										block[(location - move) + 52]++;
									}
									else
									{
										block[location]--;
										block[location - move]++;
									}
									printf("G%d ", movepiece);
									havetojump = PieceLocation[movepiece - 1].Green - havetojump;
								}
							}
							break;
						case 3:
							if (PieceLocation[movepiece - 1].Yellow == location) 					// Yellow piece move if there's a block infront of it
							{
								moved = 1;
								if (path[movepiece - 1].Yellow == 0 && BlockPath[movepiece - 1].Yellow == -1)
								{
									PieceLocation[movepiece - 1].Yellow += move;
									if (PieceLocation[movepiece - 1].Yellow > 51)
									{
										PieceLocation[movepiece - 1].Yellow -= 52;
										block[location]--;
										block[(location + move) - 52]++;
									}
									else
									{
										block[location]--;
										block[location + move]++;
									}
									printf("Y%d ", movepiece);
									havetojump = PieceLocation[movepiece - 1].Yellow + havetojump;
								}
								else if (path[movepiece - 1].Yellow == 1 && BlockPath[movepiece - 1].Yellow == -1)
								{
									PieceLocation[movepiece - 1].Yellow -= move;
									if (PieceLocation[movepiece - 1].Yellow < 0)
									{
										PieceLocation[movepiece - 1].Yellow += 52;
										block[location]--;
										block[(location - move) + 52]++;
									}
									else
									{
										block[location]--;
										block[location - move]++;
									}
									printf("Y%d ", movepiece);
									havetojump = PieceLocation[movepiece - 1].Yellow - havetojump;
								}
							}
							break;
						case 4:
							if (PieceLocation[movepiece - 1].Blue == location) 						// Blue piece move if there's a block infront of it
							{
								moved = 1;
								if (path[movepiece - 1].Blue == 0 && BlockPath[movepiece - 1].Blue == -1)
								{
									PieceLocation[movepiece - 1].Blue += move;
									if (PieceLocation[movepiece - 1].Blue > 51)
									{
										PieceLocation[movepiece - 1].Blue -= 52;
										block[location]--;
										block[(location + move) - 52]++;
									}
									else
									{
										block[location]--;
										block[location + move]++;
									}
									printf("B%d ", movepiece);
									havetojump = PieceLocation[movepiece - 1].Blue + havetojump;
								}
								else if (path[movepiece - 1].Blue == 1 && BlockPath[movepiece - 1].Blue == -1)
								{
									PieceLocation[movepiece - 1].Blue -= move;
									if (PieceLocation[movepiece - 1].Blue < 0)
									{
										PieceLocation[movepiece - 1].Blue += 52;
										block[location]--;
										block[(location - move) + 52]++;
									}
									else
									{
										block[location]--;
										block[location - move]++;
									}
									printf("B%d ", movepiece);
									havetojump = PieceLocation[movepiece - 1].Blue - havetojump;
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
			if (thepath == 0)
			{
				otherblock--;
			}
			else
			{
				otherblock++;
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
							if (BlockPath[locpiece - 1].Red == 0)						 // Red block move clockwise
							{
								PieceLocation[locpiece - 1].Red += move;
								if (PieceLocation[locpiece - 1].Red > 51)
								{
									PieceLocation[locpiece - 1].Red -= 52;
									block[location]--;
									block[(location + move) - 52]++;
								}
								else
								{
									block[location]--;
									block[location + move]++;
								}
								newpiecelocation = location + move;
								printf("R%d, ", locpiece);
							}
							else if (BlockPath[locpiece - 1].Red == 1)						 // Red block move counter clockwise
							{
								PieceLocation[locpiece - 1].Red -= move;
								if (PieceLocation[locpiece - 1].Blue < 0)
								{
									PieceLocation[locpiece - 1].Blue += 52;
									block[location]--;
									block[(location - move) + 52]++;
								}
								else
								{
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
							if (BlockPath[locpiece - 1].Green == 0)						// Green block move clockwise
							{
								PieceLocation[locpiece - 1].Green += move;
								if (PieceLocation[locpiece - 1].Green > 51)
								{
									PieceLocation[locpiece - 1].Green -= 52;
									block[location]--;
									block[(location + move) - 52]++;
								}
								else
								{
									block[location]--;
									block[location + move]++;
								}
								newpiecelocation = location + move;
								printf("G%d, ", locpiece);
							}
							else if (BlockPath[locpiece - 1].Green == 1)				// Green block move counter clockwise
							{
								PieceLocation[locpiece - 1].Green -= move;
								if (PieceLocation[locpiece - 1].Blue < 0)
								{
									PieceLocation[locpiece - 1].Blue += 52;
									block[location]--;
									block[(location + move) + 52]++;
								}
								else
								{
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
							if (BlockPath[locpiece - 1].Yellow == 0) 					// Yellow block move clockwise
							{
								PieceLocation[locpiece - 1].Yellow += move;
								if (PieceLocation[locpiece - 1].Yellow > 51)
								{
									PieceLocation[locpiece - 1].Yellow -= 52;
									block[location]--;
									block[(location + move) - 52]++;
								}
								else
								{
									block[location]--;
									block[location + move]++;
								}
								newpiecelocation = location + move;
								printf("Y%d, ", locpiece);
							}
							else if (BlockPath[locpiece - 1].Yellow == 1)				// Yellow block move counter clockwise
							{
								PieceLocation[locpiece - 1].Yellow -= move;
								if (PieceLocation[locpiece - 1].Blue < 0)
								{
									PieceLocation[locpiece - 1].Blue += 52;
									block[location]--;
									block[(location - move) + 52]++;
								}
								else
								{
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
							if (BlockPath[locpiece - 1].Blue == 0)						// Blue block move clockwise 
							{
								PieceLocation[locpiece - 1].Blue += move;
								if (PieceLocation[locpiece - 1].Blue > 51)
								{
									PieceLocation[locpiece - 1].Blue -= 52;
									block[location]--;
									block[(location + move) - 52]++;
								}
								else
								{
									block[location]--;
									block[location + move]++;
								}
								newpiecelocation = location + move;
								printf("B%d, ", locpiece);
							}
							else if (BlockPath[locpiece - 1].Blue == 1)					// Blue block move counter clockwise
							{
								PieceLocation[locpiece - 1].Blue -= move;
								if (PieceLocation[locpiece - 1].Blue < 0)
								{
									PieceLocation[locpiece - 1].Blue += 52;
									block[location]--;
									block[(location - move) + 52]++;
								}
								else
								{
									block[location]--;
									block[location - move]++;
								}
								newpiecelocation = location - move;
								printf("B%d, ", locpiece);
							}
						}
						break;
					}
				}
				if (newpiecelocation == location)
				{
					printf("from location L%d to L%d by %d units.\n", location, newpiecelocation, move);
				}
				else
				{
					printf("from location L%d to L%d by %d units in ", location, newpiecelocation, move);
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
				for (int movepiece = 1; movepiece <= 4; movepiece++)
				{
					switch (Player)
					{
					case 1:
						if (PieceLocation[movepiece - 1].Red == location)
						{
							if (path[movepiece - 1].Red == 0 && BlockPath[movepiece - 1].Red == -1) 			// Red piece move if clockwise
							{
								PieceLocation[movepiece - 1].Red += move;
								if (PieceLocation[movepiece - 1].Red > 51)
								{
									PieceLocation[movepiece - 1].Red -= 52;
									block[location] = 0;
									block[(location + move) - 52] = 1;
								}
								else
								{
									block[location] = 0;
									block[location + move] = 1;
								}
								newpiecelocation = location + move;
								printf("R%d ", movepiece);
							}
							else if (path[movepiece - 1].Red == 1 && BlockPath[movepiece - 1].Red == -1) 			// Red piece move counter clockwise
							{
								PieceLocation[movepiece - 1].Red -= move;
								if (PieceLocation[movepiece - 1].Red < 0)
								{
									PieceLocation[movepiece - 1].Red += 52;
									block[location] = 0;
									block[(location - move) + 52] = 1;
								}
								else
								{
									block[location] = 0;
									block[location - move] = 1;
								}
								newpiecelocation = location - move;
								printf("R%d ", movepiece);
							}
						}
						break;
					case 2:
						if (PieceLocation[movepiece - 1].Green == location && BlockPath[movepiece - 1].Green == -1) 		// Green piece move clockwise
						{
							if (path[movepiece - 1].Green == 0)
							{
								PieceLocation[movepiece - 1].Green += move;
								if (PieceLocation[movepiece - 1].Green > 51)
								{
									PieceLocation[movepiece - 1].Green -= 52;
									block[location] = 0;
									block[(location + move) - 52] = 1;
								}
								else
								{
									block[location] = 0;
									block[location + move] = 1;
								}
								newpiecelocation = location + move;
								printf("G%d ", movepiece);
							}
							else if (path[movepiece - 1].Green == 1 && BlockPath[movepiece - 1].Green == -1) 			// Green piece move counter clockwise
							{
								PieceLocation[movepiece - 1].Green -= move;
								if (PieceLocation[movepiece - 1].Green < 0)
								{
									PieceLocation[movepiece - 1].Green += 52;
									block[location] = 0;
									block[(location - move) + 52] = 1;
								}
								else
								{
									block[location] = 0;
									block[location - move] = 1;
								}
								newpiecelocation = location - move;
								printf("G%d ", movepiece);
							}
						}
						break;
					case 3:
						if (PieceLocation[movepiece - 1].Yellow == location && BlockPath[movepiece - 1].Yellow == -1) 		// Yellow piece move clockwisse
						{
							if (path[movepiece - 1].Yellow == 0)
							{
								PieceLocation[movepiece - 1].Yellow += move;
								if (PieceLocation[movepiece - 1].Yellow > 51)
								{
									PieceLocation[movepiece - 1].Yellow -= 52;
									block[location] = 0;
									block[(location + move) - 52] = 1;
								}
								else
								{
									block[location] = 0;
									block[location + move] = 1;
								}
								newpiecelocation = location + move;
								printf("Y%d ", movepiece);
							}
							else if (path[movepiece - 1].Yellow == 1 && BlockPath[movepiece - 1].Yellow == -1) 			// Yellow piece move counter clockwise
							{
								PieceLocation[movepiece - 1].Yellow -= move;
								if (PieceLocation[movepiece - 1].Yellow < 0)
								{
									PieceLocation[movepiece - 1].Yellow += 52;
									block[location] = 0;
									block[(location - move) + 52] = 1;
								}
								else
								{
									block[location] = 0;
									block[location - move] = 1;
								}
								newpiecelocation = location - move;
								printf("Y%d ", movepiece);
							}
						}
						break;
					case 4:
						if (PieceLocation[movepiece - 1].Blue == location && BlockPath[movepiece - 1].Blue == -1)		 // Blue piece move clockwise
						{
							if (path[movepiece - 1].Blue == 0)
							{
								PieceLocation[movepiece - 1].Blue += move;
								if (PieceLocation[movepiece - 1].Blue > 51)
								{
									PieceLocation[movepiece - 1].Blue -= 52;
									block[location] = 0;
									block[(location + move) - 52] = 1;
								}
								else
								{
									block[location] = 0;
									block[location + move] = 1;
								}
								newpiecelocation = location + move;
								printf("B%d ", movepiece);
							}
							else if (path[movepiece - 1].Blue == 1 && BlockPath[movepiece - 1].Blue == -1) 			// Blue piece move counter clockwise
							{
								PieceLocation[movepiece - 1].Blue -= move;
								if (PieceLocation[movepiece - 1].Blue < 0)
								{
									PieceLocation[movepiece - 1].Blue += 52;
									block[location] = 0;
									block[(location - move) + 52] = 1;
								}
								else
								{
									block[location] = 0;
									block[location - move] = 1;
								}
								newpiecelocation = location - move;
								printf("B%d ", movepiece);
							}
						}
						break;
					}
				}
				int newpieceorg = newpiecelocation;
				if (newpiecelocation < 0)
				{
					newpiecelocation += 52;
				}
				else if (newpiecelocation > 51)
				{
					newpiecelocation -= 52;
				}
				printf("from location L%d to L%d by %d units in ", location, newpiecelocation, move);
				if (newpieceorg > location)
				{
					printf("clockwise direction\n");
				}
				else if (newpieceorg < location)
				{
					printf("counter-clockwise direction\n");
				}
			}
		}
	}
	else if (block[location] > 1)
	{
		for (int piebl = 1; piebl <= 4; piebl++)
		{																										 // breaked block first move
			switch (Player)
			{
			case 1:
				if (path[piebl - 1].Red == location && BlockPath[piebl - 1].Red == -1)
				{
					block[location] = 1;
					Move(location, roll);
				}
				break;
			case 2:
				if (path[piebl - 1].Green == location && BlockPath[piebl - 1].Green == -1)
				{
					block[location] = 1;
					Move(location, roll);
				}
				break;
			case 3:
				if (path[piebl - 1].Yellow == location && BlockPath[piebl - 1].Yellow == -1)
				{
					block[location] = 1;
					Move(location, roll);
				}
				break;
			case 4:
				if (path[piebl - 1].Blue == location && BlockPath[piebl - 1].Blue == -1)
				{
					block[location] = 1;
					Move(location, roll);
				}
				break;
			}
		}
		block[location] = 0;
	}
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
				int havetomakeablock = 0;
				BasePiece.Red--;
				printf("Red player moves piece R%d to the starting point.\n", i);
				printf("Red player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Red), BasePiece.Red);
				if (block[26] > 0)
				{
					for (int pie = 1; pie <= 4; pie++)
					{
						if (PieceLocation[pie - 1].Blue == 26 || PieceLocation[pie - 1].Green == 26 || PieceLocation[pie - 1].Yellow == 26)		// if there any piece on X capture
						{
							printf("Red player R%d captures, ", i);
							Reset(26);
							block[26] = 1;
							break;
						}
						if (PieceLocation[pie - 1].Red == 26)
						{
							havetomakeablock = 1;
						}
					}
				}
				else if (block[26] == 0)
				{
					block[26] = 1;
				}
				PieceLocation[i - 1].Red = 26;
				HeadTail(i);                        // find the path to go(head or tail)
				if (havetomakeablock == 1)
				{
					makeBlockX();					// if any Red piece on x make a blocck
				}
				break;
			}
		}
		break;
	case 2:
		for (int i = 1; i <= 4; i++)
		{
			int havetomakeablock = 0;
			if (Piecelocation(2, i) == -10)
			{
				BasePiece.Green--;
				printf("Green player moves piece G%d to the starting point.\n", i);
				printf("Green player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Green), BasePiece.Green);
				if (block[39] > 0)
				{
					for (int pie = 1; pie <= 4; pie++)
					{
						if (PieceLocation[pie - 1].Red == 39 || PieceLocation[pie - 1].Yellow == 39 || PieceLocation[pie - 1].Blue == 39)		// if there any piece on X capture
						{
							printf("Green player G%d captures, ", i);
							Reset(39);
							block[39] = 1;
							break;
						}
						if (PieceLocation[pie - 1].Green == 39)
						{
							havetomakeablock = 1;
						}
					}
				}
				else if (block[39] == 0)
				{
					block[39] = 1;
				}
				PieceLocation[i - 1].Green = 39;
				HeadTail(i);                        // find the path to go(head or tail)
				if (havetomakeablock == 1)
				{
					makeBlockX();					// if any Green piece on x make a blocck
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
				if (block[0] > 0)
				{
					for (int pie = 1; pie <= 4; pie++)
					{
						if (PieceLocation[pie - 1].Blue == 0 || PieceLocation[pie - 1].Red == 0 || PieceLocation[pie - 1].Green == 0)   // if there any piece on X capture
						{
							printf("Yellow player Y%d captures, ", i);
							Reset(0);
							block[0] = 1;
							break;
						}
						if (PieceLocation[pie - 1].Yellow == 0)
						{
							havetomakeablock = 1;
						}
					}
				}
				else if (block[0] == 0)
				{
					block[0] = 1;
				}
				PieceLocation[i - 1].Yellow = 0;
				HeadTail(i);                        // find the path to go(head or tail)
				if (havetomakeablock == 1)
				{
					makeBlockX();					// if any Yellow piece on x make a blocck
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
				if (block[13] > 0)
				{
					for (int pie = 1; pie <= 4; pie++)
					{
						if (PieceLocation[pie - 1].Yellow == 13 || PieceLocation[pie - 1].Red == 13 || PieceLocation[pie - 1].Green == 13)		// if there any piece on X capture
						{
							printf("Blue player B%d captures, ", i);
							Reset(13);
							block[13] = 1;
							break;
						}
						if (PieceLocation[pie - 1].Blue == 13)
						{
							havetomakeablock = 1;
						}
					}
				}
				else if (block[13] == 0)
				{
					block[13] = 1;
				}
				PieceLocation[i - 1].Blue = 13;
				HeadTail(i);                        // find the path to go(head or tail)
				if (havetomakeablock == 1)
				{
					makeBlockX();					// if any Blue piece on x make a blocck
				}
				break;
			}
		}
		break;
	}
}

int Piecelocation(int randplayer, int piece)                       // get the location of the player piece
{
	int location = -10;
	switch (randplayer)
	{
	case 1:
		location = PieceLocation[piece - 1].Red;					// Red piece location
		break;
	case 2:
		location = PieceLocation[piece - 1].Green;					// Green player location
		break;
	case 3:
		location = PieceLocation[piece - 1].Yellow;					// Blue player location
		break;
	case 4:
		location = PieceLocation[piece - 1].Blue;					// Blue player location
		break;
	}
	return location;
}

void Capture(int piece, int roll)
{
	int move = roll;
	int location = Piecelocation(Player, piece);
	if (block[location] > 1)
	{
		move = roll / block[location];
	}
	int newlocation = 0;
	int newlocationplus = (location + move) % 52;
	int newlocationmin = (location - move + 52) % 52;

	switch (Player)
	{
	case 1:
		printf("Red ");																			// Red player capture
		for (int p = 1; p <= 4; p++)
		{ 
			if (block[location] > 1 && BlockPath[p - 1].Red == 0)    
			{
				if (PieceLocation[p - 1].Red == location)
				{
					printf("R%d, ", p);
					captured[p - 1].Red++;
					newlocation = newlocationplus;
				}
			}
			else if (block[location] > 1 && BlockPath[p - 1].Red == 1 && PieceLocation[p - 1].Red == newlocationmin)
			{
				if (PieceLocation[p - 1].Red == location)
				{
					printf("R%d, ", p);
					captured[p - 1].Red++;
					newlocation = newlocationmin;
				}
			}
			else if (block[location] == 1 && path[p - 1].Red == 0)
			{
				if (PieceLocation[p - 1].Red == location)
				{
					printf("R%d ", p);
					captured[p - 1].Red++;
					newlocation = newlocationplus;
				}
			}
			else if (block[location] == 1 && path[p - 1].Red == 1)
			{
				if (PieceLocation[p - 1].Red == location)
				{
					printf("R%d ", p);
					captured[p - 1].Red++;
					newlocation = newlocationmin;
				}
			}
		}
		printf("piece lands on square L%d and captures ", newlocation);
		break;
	case 2:																						// Green player capture
		printf("Green ");
		for (int p = 1; p <= 4; p++)
		{
			if (block[location] > 1 && BlockPath[p - 1].Green == 0)
			{
				if (PieceLocation[p - 1].Green == location)
				{
					printf("G%d, ", p);
					captured[p - 1].Green++;
					newlocation = newlocationplus;
				}
			}
			else if (block[location] > 1 && BlockPath[p - 1].Green == 1)
			{
				if (PieceLocation[p - 1].Green == location)
				{
					printf("G%d, ", p);
					captured[p - 1].Green++;
					newlocation = newlocationmin;
				}
			}
			else if (block[location] == 1 && path[p - 1].Green == 0)
			{
				if (PieceLocation[p - 1].Green == location)
				{
					printf("G%d ", p);
					captured[p - 1].Green++;
					newlocation = newlocationplus;
				}
			}
			else if (block[location] == 1 && path[p - 1].Green == 1)
			{
				if (PieceLocation[p - 1].Green == location)
				{
					printf("G%d ", p);
					captured[p - 1].Green++;
					newlocation = newlocationmin;
				}
			}
		}
		printf("piece lands on square L%d and captures ", newlocation);
		break;
	case 3:																					// yellow player capture
		printf("Yellow ");
		for (int p = 1; p <= 4; p++)
		{
			if (block[location] > 1 && BlockPath[p - 1].Yellow == 0)
			{
				if (PieceLocation[p - 1].Yellow == location)
				{
					printf("Y%d, ", p);
					captured[p - 1].Yellow++;
					newlocation = newlocationplus;
				}
			}
			else if (block[location] > 1 && BlockPath[p - 1].Yellow == 1)
			{
				if (PieceLocation[p - 1].Yellow == location)
				{
					printf("Y%d, ", p);
					captured[p - 1].Yellow++;
					newlocation = newlocationmin;
				}
			}
			else if (block[location] == 1 && path[p - 1].Yellow == 0)
			{
				if (PieceLocation[p - 1].Yellow == location)
				{
					printf("Y%d ", p);
					captured[p - 1].Yellow++;
					newlocation = newlocationplus;
				}
			}
			else if (block[location] == 1 && path[p - 1].Yellow == 1)
			{
				if (PieceLocation[p - 1].Yellow == location)
				{
					printf("Y%d ", p);
					captured[p - 1].Yellow++;
					newlocation = newlocationmin;
				}
			}
		}
		printf("piece lands on square L%d and captures ", newlocation);
		break;
	case 4:																								// blue player capture
		printf("Blue ");
		for (int p = 1; p <= 4; p++)
		{
			if (block[location] > 1 && BlockPath[p - 1].Blue == 0)
			{
				if (PieceLocation[p - 1].Blue == location)
				{
					printf("B%d, ", p);
					captured[p - 1].Blue++;
					newlocation = newlocationplus;
				}
			}
			else if (block[location] > 1 && BlockPath[p - 1].Blue == 1)
			{
				if (PieceLocation[p - 1].Blue == location)
				{
					printf("B%d, ", p);
					captured[p - 1].Blue++;
					newlocation = newlocationmin;
				}
			}
			else if (block[location] == 1 && path[p - 1].Blue == 0)
			{
				if (PieceLocation[p - 1].Blue == location)
				{
					printf("B%d ", p);
					captured[p - 1].Blue++;
					newlocation = newlocationplus;
				}
			}
			else if (block[location] == 1 && path[p - 1].Blue == 1)
			{
				if (PieceLocation[p - 1].Blue == location)
				{
					printf("B%d ", p);
					captured[p - 1].Blue++;
					newlocation = newlocationmin;
				}
			}
		}
		printf("piece lands on square L%d and captures ", newlocation);
		break;
	}
	Reset(newlocation);
	Move(location, roll);
}
void Reset(int newlocation)
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
				if (PieceLocation[s - 1].Red == newlocation)					// Red Player reset
				{
					PieceLocation[s - 1].Red = -10;
					captured[s - 1].Red = 0;
					++BasePiece.Red;
					path[s - 1].Red = -1;										
					BlockPath[s - 1].Red = -1;
					printf("R%d, ", s);
					Basepiece = BasePiece.Red;
					capturedplayer = 1;
					block[newlocation] = 0;
				}
				break;
			case 2:
				if (PieceLocation[s - 1].Green == newlocation)					// Green Player reset
				{
					PieceLocation[s - 1].Green = -10;
					captured[s - 1].Green = 0;
					++BasePiece.Green;
					path[s - 1].Green = -1;
					BlockPath[s - 1].Green = -1;
					printf("G%d, ", s);
					Basepiece = BasePiece.Green;
					capturedplayer = 2;
					block[newlocation] = 0;
				}
				break;
			case 3:
				if (PieceLocation[s - 1].Yellow == newlocation)					// Yellow Player reset
				{
					PieceLocation[s - 1].Yellow = -10;
					captured[s - 1].Yellow = 0;
					++BasePiece.Yellow;
					path[s - 1].Yellow = -1;
					BlockPath[s - 1].Yellow = -1;
					printf("Y%d, ", s);
					Basepiece = BasePiece.Yellow;
					capturedplayer = 3;
					block[newlocation] = 0;
				}
				break;
			case 4:
				if (PieceLocation[s - 1].Blue == newlocation)				// Blue Player reset
				{
					PieceLocation[s - 1].Blue = -10;
					captured[s - 1].Blue = 0;
					++BasePiece.Blue;
					path[s - 1].Blue = -1;
					BlockPath[s - 1].Blue = -1;
					printf("B%d, ", s);
					Basepiece = BasePiece.Blue;
					capturedplayer = 4;
					block[newlocation] = 0;
				}
				break;
			}
		}
	}
	printf("and return to the base.\n");
	PlayerCol(capturedplayer);
	printf(" player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - Basepiece), Basepiece);
}

void AI(int roll)
{
	if (roll == 6)
	{
		SixInRow++;
	}
	if (SixInRow >= 3)						  // if SIx rolled 3rd times in a row
	{
		PlayerCol(Player);
		printf(" six rolled for the third consecutive time, the roll is ignored.\n");		
		BreakBlock();          			      // break the block 
		return;
	}

	switch (Player)
	{
	case 1:
	{
		if (BasePiece.Red < 4 && roll == 6)
		{
			int cancap = CanCapture(roll);
			if (cancap > 0)
			{																// Red prioratize capture
				Capture(cancap, roll);
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
				break;
			}
		}
		if (roll == 6 && BasePiece.Red > 0)
		{ 															// Red move a piece base to board
			BaseToBoard();
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
			break;
		}
		if (BasePiece.Red < 4)
		{
			int cancap = CanCapture(roll);
			int block_piece = CanMakeBlock(roll);
			int PossibleMove = 0;
			if (cancap > 0)
			{ // Red capture if can
				Capture(cancap, roll);
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
				break;
			}
			for (int y = 1; y <= 4; y++)
			{
				if (block_piece != y && PieceLocation[y - 1].Red >= 0)
				{
					if (enterHomeStraight(roll) == 0)
					{
						Move(PieceLocation[y - 1].Red, roll); 					// Red pieces move and avoid making blocks
						PossibleMove = 1;
						break;
					}
				}
			}
			if (PossibleMove == 0 && block_piece > 0)
			{
				MakeABlock(block_piece, roll);						 // Red if any piece can move make a block
				break;
			}
			if (roll == 6)
			{
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
			}
		}
		SixInRow = 0;
	}
	break;
	case 2:
	{
		int block_piece = 0;
		if (BasePiece.Green < 4)
		{
			block_piece = CanMakeBlock(roll);
		}
		if (roll == 6 && block_piece > 0 && BasePiece.Green < 4)
		{ // Greeb prioratize making blocks
			MakeABlock(block_piece, roll);
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}
		else if (roll == 6 && BasePiece.Green > 0) 						// Greeb get a piece from base
		{
			BaseToBoard();
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}
		else if (BasePiece.Green < 4)
		{
			int piecehavetomove = 0, isitblocked = 0, blockhavetomove = 0;
			int thepiececancap = CanCapture(roll);
			block_piece = CanMakeBlock(roll);
			if (block_piece > 0)
			{
				MakeABlock(block_piece, roll);
				break;
			}
			if (thepiececancap > 0)
			{
				Capture(thepiececancap, roll);							 // Green capture if can
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
				break;
			}
			for (int loop = 1; loop <= 4; loop++)
			{
				int randompiecelocation = PieceLocation[loop - 1].Green;
				if (randompiecelocation >= 0)
				{
					if (block[randompiecelocation] == 1)
					{
						piecehavetomove = loop;
					}
					else if (block[randompiecelocation] > 1)
					{
						blockhavetomove = loop;
					}
				}
			}
			if (piecehavetomove == 0 && blockhavetomove > 0)
			{
				piecehavetomove = blockhavetomove;
			}
			if (piecehavetomove > 0)
			{
				if (enterHomeStraight(roll) == 0)
				{
					isitblocked = Move(PieceLocation[piecehavetomove - 1].Green, roll);
					if (isitblocked == 10)
					{ 															// Green break block if it blocked by another
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
		}
		SixInRow = 0;
		break;
	}
	case 3:
		if (roll == 6 && BasePiece.Yellow > 0) 									// Yellow get a piece from base
		{
			BaseToBoard();
			roll = Roll();
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}
		else if (BasePiece.Yellow < 4)
		{
			int thepiece = 0;

			for (int closetohome = 1; closetohome <= 4; closetohome++) 				// Yellow select a piece closer to home.
			{
				int hometolocation = 55;
				if (path[closetohome - 1].Yellow == 0)
				{
					if (hometolocation > (50 - PieceLocation[closetohome - 1].Yellow) && PieceLocation[closetohome - 1].Yellow >= 0)
					{
						thepiece = closetohome;
						hometolocation = 50 - PieceLocation[closetohome - 1].Yellow;
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
			int theblockpiece = CanMakeBlock(roll);
			int cancaptureY = CanCapture(roll);
			if (cancaptureY > 0)
			{
				Capture(cancaptureY, roll);
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d.\n", roll);
				AI(roll);
			}
			else if (theblockpiece > 0 && Piecelocation(3, theblockpiece) == Piecelocation(3, thepiece)) 		// Yellow Makae a blcok if can
			{
				MakeABlock(theblockpiece, roll);
				break;
			}
			else if (thepiece > 0)
			{
				if (enterHomeStraight(roll) == 0) 								// Yellow move if cant got to home straight
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
			roll = Roll();									 // Blue get a piece from base
			PlayerCol(Player);
			printf(" player rolled %d.\n", roll);
			AI(roll);
		}
		else if (BasePiece.Blue < 4)
		{
			for (int theloop = 1; theloop <= 4; theloop++)
			{
				if (PieceLocation[bluepiece - 1].Blue >= 0)
				{
					int theblockpiece = CanMakeBlock(roll);
					int cancapture = CanCapture(roll);
					if (cancapture > 0 && Piecelocation(4, bluepiece) == Piecelocation(4, cancapture)) 			// Bluue capture if can
					{
						Capture(cancapture, roll);
						roll = Roll();
						PlayerCol(Player);
						printf(" player rolled %d.\n", roll);
						AI(roll);
						break;
					}
					if (theblockpiece > 0 && Piecelocation(4, bluepiece) == Piecelocation(4, cancapture)) 			// Blue make a block if can
					{
						MakeABlock(theblockpiece, roll);
						if (roll == 6)
						{
							roll = Roll();
							PlayerCol(Player);
							printf(" player rolled %d.\n", roll);
							AI(roll);
						}
						break;
					}			
					if (enterHomeStraight(roll) == 0) 				// Blue if cant enter home staight move a piece
					{
						Move(PieceLocation[bluepiece - 1].Blue, roll);
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
				++bluepiece;					// blue player choose what to moove next (blue piece cycle)
				if (bluepiece > 4)
				{
					bluepiece = 1;
				}
			}
		}
		SixInRow = 0;
		break;
	}
}

void MakeABlock(int piece, int roll)
{
	int currentLocation, newLocation, newpath, oldpath, home;
	int *blockPath, singlePath, newblockpath;
	switch (Player)
	{
	case 1:
		currentLocation = PieceLocation[piece - 1].Red;						// get Red piece data
		blockPath = &BlockPath[piece - 1].Red;
		singlePath = path[piece - 1].Red;
		home = 24;
		break;
	case 2:
		currentLocation = PieceLocation[piece - 1].Green;						// get Green piece data
		blockPath = &BlockPath[piece - 1].Green;
		singlePath = path[piece - 1].Green;
		home = 37;
		break;
	case 3:
		currentLocation = PieceLocation[piece - 1].Yellow;						// get Yellow piece data
		blockPath = &BlockPath[piece - 1].Yellow;
		singlePath = path[piece - 1].Yellow;
		home = 50;
		break;
	case 4:
		currentLocation = PieceLocation[piece - 1].Blue;						// get Blue piece data
		blockPath = &BlockPath[piece - 1].Blue;
		singlePath = path[piece - 1].Blue;
		home = 11;
		break;
	}
	if (*blockPath == 0)														// get the location have to create a new block
	{
		newLocation = currentLocation + (roll / block[currentLocation]);
		oldpath = 0;
	}
	else if (*blockPath == 1)
	{
		newLocation = currentLocation - (roll / block[currentLocation]);
		oldpath = 1;
	}
	else if (*blockPath == -1 && singlePath == 0)
	{
		newLocation = currentLocation + (roll / block[currentLocation]);
		oldpath = 0;
	}
	else
	{
		newLocation = currentLocation - (roll / block[currentLocation]);
		oldpath = 1;
	}
	if (newLocation > 51)
	{
		newLocation -= 52;
	}
	else if (newLocation < 0)
	{
		newLocation += 51;
	}
	for (int otherpiece = 1; otherpiece < 4; otherpiece++)
	{
		switch (Player)																	// Get the other piece/block path
		{
		case 1:
			if (PieceLocation[otherpiece - 1].Red == newLocation)								
			{
				if (block[newLocation] > 1)
				{
					newpath = BlockPath[otherpiece - 1].Red;
				}
				else
				{
					newpath = path[otherpiece - 1].Red;
				}
			}
			break;
		case 2:
			if (PieceLocation[otherpiece - 1].Green == newLocation)
			{
				if (block[newLocation] > 1)
				{
					newpath = BlockPath[otherpiece - 1].Green;
				}
				else
				{
					newpath = path[otherpiece - 1].Green;
				}
			}
			break;
		case 3:
			if (PieceLocation[otherpiece - 1].Yellow == newLocation)
			{
				if (block[newLocation] > 1)
				{
					newpath = BlockPath[otherpiece - 1].Yellow;
				}
				else
				{
					newpath = path[otherpiece - 1].Yellow;
				}
			}
			break;
		case 4:
			if (PieceLocation[otherpiece - 1].Blue == newLocation)
			{
				if (block[newLocation] > 1)
				{
					newpath = BlockPath[otherpiece - 1].Blue;
				}
				else
				{
					newpath = path[otherpiece - 1].Blue;
				}
			}
			break;
		}
	}
	if (newpath != oldpath)											// Get the path of the new block
	{
		int homeToPiece;
		if (newpath == 0)
		{
			homeToPiece = home - newLocation;
		}
		else if (newpath == 1)
		{
			homeToPiece = newLocation - 2;
		}
		if (homeToPiece < 0)
		{
			homeToPiece += 51;
		}
		else if (homeToPiece > 51)
		{
			homeToPiece -= 51;
		}
		if (homeToPiece >= 52 - homeToPiece)
		{
			newblockpath = oldpath;
		}
		else if (homeToPiece < 52 - homeToPiece)
		{
			newblockpath = newpath;
		}
	}
	else
	{
		newblockpath = newpath;
	}
	block[newLocation] = block[newLocation] + block[currentLocation];    // move the block
	block[currentLocation] = 0;
	PlayerCol(Player);
	printf(" Player ");
	for (int justloop = 1; justloop <= 4; justloop++)
	{
		switch (Player)                                                       // Set the new location to the piece/pieces
		{
		case 1:
			if (PieceLocation[justloop - 1].Red == currentLocation)
			{
				PieceLocation[justloop - 1].Red = newLocation;
				printf("R%d, ", justloop);
			}
			if (PieceLocation[justloop - 1].Red == currentLocation)
			{
				BlockPath[justloop - 1].Red = newblockpath;
			}
			break;
		case 2:
			if (PieceLocation[justloop - 1].Green == currentLocation)
			{
				PieceLocation[justloop - 1].Green = newLocation;
				printf("G%d, ", justloop);
			}
			if (PieceLocation[justloop - 1].Green == newLocation)
			{
				BlockPath[justloop - 1].Green = newblockpath;
			}
			break;
		case 3:
			if (PieceLocation[justloop - 1].Yellow == currentLocation)
			{
				PieceLocation[justloop - 1].Yellow = newLocation;
				printf("Y%d, ", justloop);
			}
			if (PieceLocation[justloop - 1].Yellow == newLocation)
			{
				BlockPath[justloop - 1].Yellow = newblockpath;
			}
			break;
		case 4:
			if (PieceLocation[justloop - 1].Blue == currentLocation)
			{
				PieceLocation[justloop - 1].Blue = newLocation;
				printf("B%d, ", justloop);
			}
			if (PieceLocation[justloop - 1].Blue == newLocation)
			{
				BlockPath[justloop - 1].Blue = newblockpath;
			}
			break;
		}
	}
	printf("piece move from %d to %d and make a block.\n", currentLocation, newLocation);
}

void HeadTail(int piece)
{

	int headtail = rand() % 2;                         //  0 = clockwise  1 = counterwise.
	switch (Player)                                    // set the path for the piece
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

void BreakBlock()
{

	for (int blockpiece1 = 1; blockpiece1 <= 4; blockpiece1++)
	{
		for (int blockpiece2 = blockpiece1; blockpiece2 <= 4; blockpiece2++)
		{
			switch (Player)																							// remove the block path from the piece
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
			switch (Player)
			{
			case 1:
				if (PieceLocation[canmakepiece - 1].Red >= 0 && block[PieceLocation[canmakepiece - 1].Red > 0])
				{
					if (roll / block[PieceLocation[canmakepiece - 1].Red] == 0)                                                                      // Check if Red can make a block
					{
						break;
					}
					int maxloc = (PieceLocation[canmakepiece - 1].Red + (roll / block[PieceLocation[canmakepiece - 1].Red])) % 52;
					int minloc = ((PieceLocation[canmakepiece - 1].Red - (roll / block[PieceLocation[canmakepiece - 1].Red])) + 52 ) % 52;
					
					if (maxloc == PieceLocation[otherpiece - 1].Red && canmakepiece != otherpiece && BlockPath[canmakepiece - 1].Red == 0)
					{
						block_piece = canmakepiece;
					}
					else if (minloc == PieceLocation[otherpiece - 1].Red && canmakepiece != otherpiece && BlockPath[canmakepiece - 1].Red == 1)
					{
						block_piece = canmakepiece;
					}
					else if (maxloc == PieceLocation[otherpiece - 1].Red && canmakepiece != otherpiece && path[canmakepiece - 1].Red == 0)
					{
						block_piece = canmakepiece;
					}
					else if (minloc == PieceLocation[otherpiece - 1].Red && canmakepiece != otherpiece && path[canmakepiece - 1].Red == 1)
					{
						block_piece = canmakepiece;
					}
				}

				break;
			case 2:
				if (PieceLocation[canmakepiece - 1].Green >= 0 && block[PieceLocation[canmakepiece - 1].Green] > 0)
				{
					if (roll / block[PieceLocation[canmakepiece - 1].Green] == 0)                                                                      // Check if Green can make a block
					{
						break;
					}
					int maxloc = (PieceLocation[canmakepiece - 1].Green + (roll / block[PieceLocation[canmakepiece - 1].Green])) % 52;
					int minloc = ((PieceLocation[canmakepiece - 1].Green - (roll / block[PieceLocation[canmakepiece - 1].Green])) + 52) % 52;
					
					if (maxloc == PieceLocation[otherpiece - 1].Green && canmakepiece != otherpiece && BlockPath[canmakepiece - 1].Green == 0)
					{
						block_piece = canmakepiece;
					}
					else if (minloc == PieceLocation[otherpiece - 1].Green && canmakepiece != otherpiece && BlockPath[canmakepiece - 1].Green == 1)
					{
						block_piece = canmakepiece;
					}
					else if (maxloc == PieceLocation[otherpiece - 1].Green && canmakepiece != otherpiece && path[canmakepiece - 1].Green == 0)
					{
						block_piece = canmakepiece;
					}
					else if (minloc == PieceLocation[otherpiece - 1].Green && canmakepiece != otherpiece && path[canmakepiece - 1].Green == 1)
					{
						block_piece = canmakepiece;
					}
				}
				break;
			case 3:
				if (PieceLocation[canmakepiece - 1].Yellow >= 0 && block[PieceLocation[canmakepiece - 1].Yellow] > 0)
				{
					if (roll / block[PieceLocation[canmakepiece - 1].Yellow] == 0)                                                                      // Check if Yellow can make a block
					{
						break;
					}
					int maxloc = (PieceLocation[canmakepiece - 1].Yellow + (roll / block[PieceLocation[canmakepiece - 1].Yellow]) )% 52;
					int minloc = ((PieceLocation[canmakepiece - 1].Yellow - (roll / block[PieceLocation[canmakepiece - 1].Yellow])) + 52 ) % 52;
				
					if (maxloc == PieceLocation[otherpiece - 1].Yellow && canmakepiece != otherpiece && BlockPath[canmakepiece - 1].Yellow == 0)
					{
						block_piece = canmakepiece;
					}
					else if (minloc == PieceLocation[otherpiece - 1].Yellow && canmakepiece != otherpiece && BlockPath[canmakepiece - 1].Yellow == 1)
					{
						block_piece = canmakepiece;
					}
					else if (maxloc == PieceLocation[otherpiece - 1].Yellow && canmakepiece != otherpiece && path[canmakepiece - 1].Yellow == 0)
					{
						block_piece = canmakepiece;
					}
					else if (minloc == PieceLocation[otherpiece - 1].Yellow && canmakepiece != otherpiece && path[canmakepiece - 1].Yellow == 1)
					{
						block_piece = canmakepiece;
					}
				}
				break;
			case 4:
				if (PieceLocation[canmakepiece - 1].Blue >= 0 && block[PieceLocation[canmakepiece - 1].Blue] > 0)
				{
					if (roll / block[PieceLocation[canmakepiece - 1].Blue] == 0)                                                                         // Check if Blue can make a block
					{
						break;
					}
					int maxloc = (PieceLocation[canmakepiece - 1].Blue + (roll / block[PieceLocation[canmakepiece - 1].Blue])) % 52;
					int minloc = ((PieceLocation[canmakepiece - 1].Blue - (roll / block[PieceLocation[canmakepiece - 1].Blue])) + 52 ) % 52;
					
					if (maxloc == PieceLocation[otherpiece - 1].Blue && canmakepiece != otherpiece && BlockPath[canmakepiece - 1].Blue == 0)
					{
						block_piece = canmakepiece;
					}
					else if (minloc == PieceLocation[otherpiece - 1].Blue && canmakepiece != otherpiece && BlockPath[canmakepiece - 1].Blue == 1)
					{
						block_piece = canmakepiece;
					}
					else if (maxloc == PieceLocation[otherpiece - 1].Blue && canmakepiece != otherpiece && path[canmakepiece - 1].Blue == 0)
					{
						block_piece = canmakepiece;
					}
					else if (minloc == PieceLocation[otherpiece - 1].Blue && canmakepiece != otherpiece && path[canmakepiece - 1].Blue == 1)
					{
						block_piece = canmakepiece;
					}
				}
				break;
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
			if (BlockPath[cappiece - 1].Red == 0 && PieceLocation[cappiece - 1].Red >= 0)                 // Red Block captures clockwise
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red + (roll / block[PieceLocation[cappiece - 1].Red]);
					if (caploc > 51)
					{
						caploc -= 52;
					}
					if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Red] >= block[caploc])
					{
						cancapture = cappiece;
					}
				}
			}
			else if (BlockPath[cappiece - 1].Red == 1 && PieceLocation[cappiece - 1].Red >= 0)				// Red block captures counter clockwise
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red - (roll / block[PieceLocation[cappiece - 1].Red]);
					if (caploc < 0)
					{
						caploc += 52;
					}
					if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Red] >= block[caploc])
					{
						cancapture = cappiece;
					}
				}
			}
			else if (path[cappiece - 1].Red == 0 && PieceLocation[cappiece - 1].Red >= 0 && BlockPath[cappiece - 1].Red == -1)					// Red piece captures clockwise
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red + roll;
					if (caploc > 51)
					{
						caploc -= 52;
					}
					if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Red] >= block[caploc])
					{
						cancapture = cappiece;
					}
				}
			}
			else if (path[cappiece - 1].Red == 1 && PieceLocation[cappiece - 1].Red >= 0 && BlockPath[cappiece - 1].Red == -1)					// Red piece captures counter clockwise
			{	
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Red - roll;
					if (caploc < 0)
					{
						caploc += 52;
					}
					if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Red] >= block[caploc])
					{
						cancapture = cappiece;
					}
				}
			}
			break;
		case 2:
			if (BlockPath[cappiece - 1].Green == 0 && PieceLocation[cappiece - 1].Green >= 0)											// Green block captures clockwise
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Green + (roll / block[PieceLocation[cappiece - 1].Green]);
					if (caploc > 51)
					{
						caploc -= 52;
					}
					if ((caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Green] >= block[caploc])
					{
						cancapture = cappiece;
					}
				}
			}
			else if (BlockPath[cappiece - 1].Green == 1 && PieceLocation[cappiece - 1].Green >= 0)                                        // Green block captures counter clockwise
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Green - (roll / block[PieceLocation[cappiece - 1].Green]);
					if (caploc < 0)
					{
						caploc += 52;
					}
					if ((caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Green] >= block[caploc])
					{
						cancapture = cappiece;
					}
				}
			}
			else if (path[cappiece - 1].Green == 0 && PieceLocation[cappiece - 1].Green >= 0 && BlockPath[cappiece - 1].Green == -1)				// Green piece captures clockwise
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Green + roll;
					if (caploc > 51)
					{
						caploc -= 52;
					}
					if ((caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Green] >= block[caploc])
					{
						cancapture = cappiece;
					}
				}
			}
			else if (path[cappiece - 1].Green == 1 && PieceLocation[cappiece - 1].Green >= 0 && BlockPath[cappiece - 1].Green == -1)                 // Green piece captures counter clockwise
			{
				for (int othercap = 1; othercap <= 4; othercap++)
				{
					int caploc = PieceLocation[cappiece - 1].Green - roll;
					if (caploc < 0)
					{
						caploc += 52;
					}
					if ((caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Green] >= block[caploc])
					{
						cancapture = cappiece;
					}
				}
			}
			break;
		case 3:
				if (BlockPath[cappiece - 1].Yellow == 0 && PieceLocation[cappiece - 1].Yellow >= 0)												// Yellow block captures clockwise
				{
					for (int othercap = 1; othercap <= 4; othercap++)
					{
						int caploc = PieceLocation[cappiece - 1].Yellow + (roll / block[PieceLocation[cappiece - 1].Yellow]);
						if (caploc > 51)
						{
							caploc -= 52;
						}
						if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Yellow] >= block[caploc])
						{
							cancapture = cappiece;
						}
					}
				}
				else if (BlockPath[cappiece - 1].Yellow == 1 && PieceLocation[cappiece - 1].Yellow >= 0)										// Yellow block captures counter clockwise
				{
					for (int othercap = 1; othercap <= 4; othercap++)
					{
						int caploc = PieceLocation[cappiece - 1].Yellow - (roll / block[PieceLocation[cappiece - 1].Yellow]);
						if (caploc < 0)
						{
							caploc += 52;
						}
						if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Yellow] >= block[caploc])
						{
							cancapture = cappiece;
						}
					}
				}
				else if (path[cappiece - 1].Yellow == 0 && PieceLocation[cappiece - 1].Yellow >= 0 && BlockPath[cappiece - 1].Yellow == -1)           // Yellow piece captures clockwise
				{
					for (int othercap = 1; othercap <= 4; othercap++)
					{
						int caploc = PieceLocation[cappiece - 1].Yellow + roll;
						if (caploc > 51)
						{
							caploc -= 52;
						}
						if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Yellow] >= block[caploc])
						{
							cancapture = cappiece;
						}
					}
				}
				else if (path[cappiece - 1].Yellow == 1 && PieceLocation[cappiece - 1].Yellow >= 0 && BlockPath[cappiece - 1].Yellow == -1)          // Yellow piece captures counter clockwise
				{
					for (int othercap = 1; othercap <= 4; othercap++)
					{
						int caploc = PieceLocation[cappiece - 1].Yellow - roll;
						if (caploc < 0)
						{
							caploc += 52;
						}
						if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Red || caploc == PieceLocation[othercap - 1].Blue) && block[PieceLocation[cappiece - 1].Yellow] >= block[caploc])
						{
							cancapture = cappiece;
						}
					}
				}
				break;
			case 4:
				if (BlockPath[cappiece - 1].Blue == 0 && PieceLocation[cappiece - 1].Blue >= 0)                                             // Blue block captures clockwise
				{
					for (int othercap = 1; othercap <= 4; othercap++)
					{
						int caploc = PieceLocation[cappiece - 1].Blue + (roll / block[PieceLocation[cappiece - 1].Blue]);
						if (caploc > 51)
						{
							caploc -= 52;
						}
						if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Red) && block[PieceLocation[cappiece - 1].Blue] >= block[caploc])
						{
							cancapture = cappiece;
						}
					}
				}
				else if (BlockPath[cappiece - 1].Blue == 1 && PieceLocation[cappiece - 1].Blue >= 0)									// Blue block captures counter clockwise
				{
					for (int othercap = 1; othercap <= 4; othercap++)
					{
						int caploc = PieceLocation[cappiece - 1].Blue - (roll / block[PieceLocation[cappiece - 1].Blue]);
						if (caploc < 0)
						{
							caploc += 52;
						}
						if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Red) && block[PieceLocation[cappiece - 1].Blue] >= block[caploc])
						{
							cancapture = cappiece;
						}
					}
				}
				else if (path[cappiece - 1].Blue == 0 && PieceLocation[cappiece - 1].Blue >= 0 && BlockPath[cappiece - 1].Blue == -1)			// Blue piece captures clockwise
				{
					for (int othercap = 1; othercap <= 4; othercap++)
					{
						int caploc = PieceLocation[cappiece - 1].Blue + roll;
						if (caploc > 51)
						{
							caploc -= 52;
						}
						if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Red) && block[PieceLocation[cappiece - 1].Blue] >= block[caploc])
						{
							cancapture = cappiece;
						}
					}
				}
				else if (path[cappiece - 1].Blue == 1 && PieceLocation[cappiece - 1].Blue >= 0 && BlockPath[cappiece - 1].Blue == -1)			// Blue piece captures counter clockwise
				{
					for (int othercap = 1; othercap <= 4; othercap++)
					{
						int caploc = PieceLocation[cappiece - 1].Blue - roll;
						if (caploc < 0)
						{
							caploc += 52;
						}
						if ((caploc == PieceLocation[othercap - 1].Green || caploc == PieceLocation[othercap - 1].Yellow || caploc == PieceLocation[othercap - 1].Red) && block[PieceLocation[cappiece - 1].Blue] >= block[caploc])
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

void summary()
{
																															              // Summary of the pieces on the board
	printf("Red player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", 4 - BasePiece.Red, BasePiece.Red);             
	printf("Green player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", 4 - BasePiece.Green, BasePiece.Green);
	printf("Yellow player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", 4 - BasePiece.Yellow, BasePiece.Yellow);
	printf("Blue player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", 4 - BasePiece.Blue, BasePiece.Blue);
	printf("---------------------------------------\n");
	for (int i = 1; i <= 4; i++)																											// Summary of the pieces locations
	{
		if (PieceLocation[i - 1].Red >= 0)
		{
			printf("Red R%d piece location L%d.\n", i, PieceLocation[i - 1].Red);
			printf("Red R%d piece captured %d pieces.\n", i, captured[i - 1].Red);
		}
	}
	printf("\n");
	for (int i = 1; i <= 4; i++)
	{
		if (PieceLocation[i - 1].Green >= 0)
		{
			printf("Green G%d piece location L%d.\n", i, PieceLocation[i - 1].Green);
			printf("Green G%d piece captured %d pieces.\n", i, captured[i - 1].Green);
		}
	}
	printf("\n");
	for (int i = 1; i <= 4; i++)
	{
		if (PieceLocation[i - 1].Yellow >= 0)
		{
			printf("Yellow Y%d piece location L%d.\n", i, PieceLocation[i - 1].Yellow);
			printf("Yellow Y%d piece captured %d pieces.\n", i, captured[i - 1].Yellow);
		}
	}
	printf("\n");
	for (int i = 1; i <= 4; i++)
	{
		if (PieceLocation[i - 1].Blue >= 0)
		{
			printf("Blue B%d piece location L%d.\n", i, PieceLocation[i - 1].Blue);
			printf("Blue B%d piece captured %d pieces.\n", i, captured[i - 1].Blue);
		}
	}
	printf("---------------------------------------\n");																	//summary of the pieces in home
	printf("Red player has %d pieces at home.\n", GotHome.Red);
	printf("Green player has %d pieces at home.\n", GotHome.Green);
	printf("Yellow player has %d pieces at home.\n", GotHome.Yellow);
	printf("Blue player has %d pieces at home.\n", GotHome.Blue);
	printf("---------------------------------------\n");
}

void makeBlockX()
{
	int count = 0, locationpiece;
	for (int pieceX = 1; pieceX <= 4; pieceX++)
	{
		switch (Player)
		{
		case 1:
			if (PieceLocation[pieceX - 1].Red == 26)                                         //  Red make a block when it comes to starting point X
			{
				BlockPath[pieceX - 1].Red = 0;
				locationpiece = 26;
				count++;
			}
			break;
		case 2:
			if (PieceLocation[pieceX - 1].Green == 39)										//  Green make a block when it comes to starting point X
			{
				BlockPath[pieceX - 1].Green = 0;
				count++;
				locationpiece = 39;
			}
			break;
		case 3:
			if (PieceLocation[pieceX - 1].Yellow == 0)										//  Yellow make a block when it comes to starting point X
			{
				BlockPath[pieceX - 1].Yellow = 0;
				count++;
				locationpiece = 0;
			}
			break;
		case 4:
			if (PieceLocation[pieceX - 1].Blue == 13)										//  Blue make a block when it comes to starting point X
			{
				BlockPath[pieceX - 1].Blue = 0;
				count++;
				locationpiece = 13;
			}
			break;
		}
	}
	block[locationpiece] = count;
}

int piecepath(int location)
{
	int returnpath = 0;
	if (block[location] == 1)			                                   // get the piece path of a piece
	{
		for (int piecex = 1; piecex <= 4; piecex++) 
		{
			switch (Player)
			{
			case 1:
				if (PieceLocation[piecex - 1].Red == location && path[piecex - 1].Red == 1)
				{
					returnpath = 1;
				}
				break;
			case 2:
				if (PieceLocation[piecex - 1].Green == location && path[piecex - 1].Green == 1)
				{
					returnpath = 1;
				}
				break;
			case 3:
				if (PieceLocation[piecex - 1].Yellow == location && path[piecex - 1].Yellow == 1)
				{
					returnpath = 1;
				}
				break;
			case 4:
				if (PieceLocation[piecex - 1].Blue == location && path[piecex - 1].Blue == 1)
				{
					returnpath = 1;
				}
				break;
			}
		}
	}
	else if (block[location] > 1)											// get the piece path of a block
	{
		for (int piecex = 1; piecex <= 4; piecex++)
		{
			switch (Player)
			{
			case 1:
				if (PieceLocation[piecex - 1].Red == location && BlockPath[piecex - 1].Red == 1)
				{
					returnpath = 1;
				}
				break;
			case 2:
				if (PieceLocation[piecex - 1].Green == location && BlockPath[piecex - 1].Green == 1)
				{
					returnpath = 1;
				}
				break;
			case 3:
				if (PieceLocation[piecex - 1].Yellow == location && BlockPath[piecex - 1].Yellow == 1)
				{
					returnpath = 1;
				}
			case 4:
				if (PieceLocation[piecex - 1].Blue == location && BlockPath[piecex - 1].Blue == 1)
				{
					returnpath = 1;
				}
				break;
			}
		}
	}
	return returnpath;
}

int enterHomeStraight(int roll)
{
    int approachCell = -1;
    int homeEntrance = -1;

   																 // Determine the approach cell and home entrance based on the current player
    switch (Player)
    {
    case 1:							 // Red
        approachCell = 25;
        homeEntrance = 26;
        break;
    case 2:							 // Green
        approachCell = 38;
        homeEntrance = 39;
        break;
    case 3:						 // Yellow
        approachCell = 51;
        homeEntrance = 0;
        break;
    case 4: 					// Blue
        approachCell = 12;
        homeEntrance = 13;
        break;
    }

   																			 // Check all pieces for the current player
    for (int currentPiece = 0; currentPiece < 4; currentPiece++)
    {
        int currentLocation = -1;
        int hasCaptured = 0;

       																			 // Get the current location and capture status for the piece
        switch (Player)
        {
        case 1:													 // Red
            currentLocation = PieceLocation[currentPiece].Red;
            hasCaptured = captured[currentPiece].Red > 0;
            break;
        case 2:													 // Green
            currentLocation = PieceLocation[currentPiece].Green;
            hasCaptured = captured[currentPiece].Green > 0;
            break;
        case 3:														// Yellow
            currentLocation = PieceLocation[currentPiece].Yellow;
            hasCaptured = captured[currentPiece].Yellow > 0;
            break;
        case 4: 													// Blue
            currentLocation = PieceLocation[currentPiece].Blue;
            hasCaptured = captured[currentPiece].Blue > 0;
            break;
        }

        if (!hasCaptured)
        {
            continue; 											// This piece hasn't captured, move to the next piece
        }

      															  // Check if the piece is at or past the approach cell
        int distanceToHome = 0;
        if (currentLocation == approachCell)
        {
            distanceToHome = 6; 									// 5 home straight cells + 1 to reach 'Home'
        }
        else if (currentLocation > approachCell && currentLocation < homeEntrance)
        {
            distanceToHome = homeEntrance - currentLocation;
        }
        else
        {
            continue; 												// This piece is not at or past the approach cell, move to the next piece
        }

       																 // Check if the roll is exact to enter home
        if (roll == distanceToHome)
        {
          															  // Move the piece to home
            switch (Player)
            {
            case 1:
                PieceLocation[currentPiece].Red = -2; // Assuming -2 represents 'Home'
                GotHome.Red++;
                break;
            case 2:
                PieceLocation[currentPiece].Green = -2;
                GotHome.Green++;
                break;
            case 3:
                PieceLocation[currentPiece].Yellow = -2;
                GotHome.Yellow++;
                break;
            case 4:
                PieceLocation[currentPiece].Blue = -2;
                GotHome.Blue++;
                break;
            }

            printf("%c%d has entered Home!\n", "RGYB"[Player - 1], currentPiece + 1);
            return 1; 
        }
    }

    return 0;
}