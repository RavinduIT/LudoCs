#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"

int main()
{
	int Game = 100;
	int round = 1;
	srand(time(0));
	setbuf(stdout, 0);
	SetValues(); // set values to starting point
	intro();
	ChooseFirstPlayer();
	printf("\n");
	int startPlayer = Player;
	while (Game)
	{
		if(startPlayer == Player) {
			printf("\n\t----Round %d---- \n", round);
			round++;
		}
		SixInRow = 0;
		if (Player > 4)
		{
			Player = 1;
		}
		int CurrentRoll = Roll();
		PlayerCol(Player);
		printf(" player rolled %d.\n", CurrentRoll);
		AI(CurrentRoll);

		Player++;
		Game--;
		if (startPlayer == Player) {
			printf("\n");
			summury();
		}
		if (Home.Red == 4 || Home.Green == 4 || Home.Yellow == 4 || Home.Blue == 4)
		{
			Game = 0;
		}
	}
	PlayerCol(Player);
	printf(" Won the game !\n");

	return 0;
}
