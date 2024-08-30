#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"

int main()
{
	int Game = 1, round = 1;
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
		if (startPlayer == Player) {
			printf("\n");
			summury();
			for(int i = 0; i <= 51; i++) {
			printf(" %d.%d\t",i, block[i]);
		}
	}
		}
		if (GotHome.Red == 4 || GotHome.Green == 4 || GotHome.Yellow == 4 || GotHome.Blue == 4)
		{
			Game = 0;
		}
	PlayerCol(Player);
	printf(" Won the game !\n");

	return 0;
}
